import json
import time
import requests
from bs4 import BeautifulSoup   

# Helper
def isValidChar(character):
    return (character >= 'A' and character <= 'Z') or (character >= 'a' and character <= 'z') or (character == '.') or (character >= '0' and character <= '9')

def cleanText(textToClean):
    # Cleaning card_name, as they have trailing spaces for some reason
    newText = ""
    tmpText = ""
    startSpaces = True
    for c in textToClean:
        if isValidChar(c):
            startSpaces = False
            tmpText += c
        elif not startSpaces:
            newText += tmpText 
            tmpText = " "
            startSpaces = True
    if not startSpaces:
        newText += tmpText
    return newText
    
def cardInfo(cardURL): 
    global missingCards, cardInformation
    req = "https://www.deckshop.pro" + cardURL
    resp = requests.get(req)
    if (200 < resp.status_code >= 300):
        print(f"Failed getting card at : {req}")
        missingCards.append(cardURL)
        return 1
    # Get specific card url
    soup = BeautifulSoup(resp.text, 'html.parser')   
    main_container = soup.find("section", class_= "bg-linear-to-br from-gray-body to-gray-dark px-page py-3")

    # Find concrete stats about the card
    card_name = cleanText(main_container.find("h1").text)
    card_rarity = cleanText(main_container.find("span").text)
    
    # Find Other stats {like Damage, Tower Damage, range, count, etc}
    stats_table = main_container.find("table", class_="")
    all_card_stats = stats_table.find_all("tr")

    # Create a new empty list for the card. All cards have a rarity, so store it first
    cardInformation[card_name] = [{"Rarity": card_rarity}]
    for stat in all_card_stats:
        stat_name = cleanText(stat.find("th", class_="text-gray-muted font-normal").text)
        stat_info = cleanText(stat.find("td", class_="text-right").text)
        cardInformation[card_name].append({stat_name: stat_info})
    # print(f"Stored card information {card_name}")

def main():
    global missingCards, cardInformation

    # ========= ALL CLASH ROYALE CARDS IN JSON =========== 
    # EXCLUDING EVOLUTIONS
    response = requests.get("https://www.deckshop.pro/card/list")
    soup = BeautifulSoup(response.text, 'html.parser')

    # Find Main_Container
    main_container = soup.find("div", class_= "grid md:grid-cols-2 gap-5")
    # Find sorted list (we'll use sorted_by_rarity as it won't matter)
    all_cards_container = main_container.find_all("section", class_="")
    sorted_by_rarity = all_cards_container[0]
    sorted_by_elixir = all_cards_container[1]

    # String list of the missing cards
    missingCards = []
    # Format : {Card_Name : [{Rarity : Rarity}, Stats : as shown on website in their respective order]}
    cardInformation = {}          
    
    # Get all cards found and parse it to get details
    all_cards = sorted_by_rarity.find_all("a")
    print(f"Found {len(all_cards)} cards in Clash Royale (Excluding Evolutions)")
    for cardLink in all_cards:
        cardInfo(cardLink.get("href"))

    # Try again with failed
    print(f"{len(missingCards)} cards failed to retrieve. Retrying all of them...")
    for cardLink in missingCards:
        cardInfo(cardLink)

    # Store information inside a json
    payload = {
        "missingCards": missingCards,
        "cardInformation": cardInformation,
    }
    with open("ClashCards.json", "w") as f:
        json.dump(payload, f, indent = 1)

    print("Successfully executed!")
    return 0

main()