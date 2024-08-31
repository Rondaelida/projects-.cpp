EXECUTE_FILE = brick_game
TEST_EXECUTE_FILE = snake_test
DIR_INSTALL = out
REPORT = REPORT.html
REPORT_DIR = Report
EXCLUDE_FILES = "unit_tests/*" "components/Interfaces/IModel.h"
EXCLUDE_REPORT = $(foreach file, $(EXCLUDE_FILES), --exclude $(file))

all: install

install:
	make uninstall
	@mkdir -p ./out
	cd build && cmake . && make && mv $(EXECUTE_FILE) ../out
	make run

run:
	cd $(DIR_INSTALL) && ./$(EXECUTE_FILE)

uninstall:
	@rm -rf $(DIR_INSTALL)

gen_test:
	cd ./unit_tests/build && cmake . && make && mv $(TEST_EXECUTE_FILE) ..

tests:
	make gen_test
	cd ./unit_tests && ./$(TEST_EXECUTE_FILE)
	@rm -rf ./unit_tests/records

val: gen_test
	cd ./unit_tests && valgrind --tool=memcheck --leak-check=yes ./$(TEST_EXECUTE_FILE)

gcov_report: tests
	@mkdir -p $(REPORT_DIR)
	@cd ./unit_tests/build/CMakeFiles && find . \( -name "*.gcno" -o -name "*.gcda"  \) -exec mv {} ../../../$(REPORT_DIR)/ \;
	~/.local/bin/gcovr $(REPORT_DIR)/ $(EXCLUDE_REPORT) --html --html-details -o $(REPORT)
	@make move_report

peer: gcov_report
	@open $(REPORT_DIR)/$(REPORT)

dvi:
	@google-chrome ./doc/html/index.html

dist:
	@if [ -d "$(DIR_INSTALL)" ]; then \
		(cd $(DIR_INSTALL) && tar -cf BrickGame.tar . && mv BrickGame.tar ../); \
	else \
		echo "Directory $(DIR_INSTALL) does not exist."; \
	fi

move_report:
	@mv *.html *.css $(REPORT_DIR)

clean :
	@cd build && find . -mindepth 1 -not -name "CMakeLists.txt" -exec rm -rf {} +
	@cd unit_tests/build && find . -mindepth 1 -not -name "CMakeLists.txt" -exec rm -rf {} +
	@rm -rf unit_tests/*_test $(REPORT_DIR) unit_tests/records

rebuild: clean install
