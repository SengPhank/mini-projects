run:
	@mkdir -p build
	@cd build && cmake ..
	@cd build && cmake --build .
	@./build/WordleSolver
	@$(MAKE) clean

clean:
	@rm -rf build
