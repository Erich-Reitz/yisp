#include <source_location>
#include <variant>
#include <vector>


#include "./minunit.hpp"

#include "../src/filereads.hpp"
#include "test_utils.hpp"

int tests_run = 0;



const static char *integration_test_addition() {
  const std::string test_name = "addition";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}


const static char *integration_test_subtraction() {
  const std::string test_name = "subtraction";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_multiplication() {
  const std::string test_name = "multiplication";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}


const static char *integration_test_number_literals() {
  const std::string test_name = "number_literals";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_string_literals() {
  const std::string test_name = "string_literals";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}


const static char *integration_test_sum2() {
  const std::string test_name = "sum2_func";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_nested_operator_expression() {
  const std::string test_name = "nested_operator_expression";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}


const static char *integration_test_list_function() {
  const std::string test_name = "list_function";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_basic_variable() {
  const std::string test_name = "basic_variable";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}


const static char *integration_test_set_var_to_quoted_list() {
  const std::string test_name = "set_var_to_quoted_list";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}


const static char *integration_test_is_number() {
  const std::string test_name = "NUMBER?";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}


const static char *integration_test_is_list() {
  const std::string test_name = "LIST?";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}


const static char *integration_test_is_symbol() {
  const std::string test_name = "SYMBOL?";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_is_nil() {
  const std::string test_name = "NIL?";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_eq() {
  const std::string test_name = "eq";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_AND() {
  const std::string test_name = "AND?";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}


const static char *integration_test_factorial() {
  const std::string test_name = "factorial";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}


const static char *integration_test_less() {
  const std::string test_name = "less";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_greater() {
  const std::string test_name = "greater";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_division() {
  const std::string test_name = "division";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}



const static char *integration_test_OR() {
  const std::string test_name = "OR?";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_car() {
  const std::string test_name = "car";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_cdr() {
  const std::string test_name = "cdr";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}

const static char *integration_test_cons() {
  const std::string test_name = "cons";
  return runIntegrationTest(test_name, std::source_location::current().function_name());
}





const static char *all_tests() {
  // integration tests
  mu_run_test(integration_test_addition);
  mu_run_test(integration_test_subtraction);
  mu_run_test(integration_test_multiplication);
  mu_run_test(integration_test_number_literals);
  mu_run_test(integration_test_string_literals);
  mu_run_test(integration_test_sum2);
  mu_run_test(integration_test_nested_operator_expression);
  mu_run_test(integration_test_list_function);
  mu_run_test(integration_test_basic_variable);
  mu_run_test(integration_test_is_number) ;
  mu_run_test(integration_test_is_list);
  mu_run_test(integration_test_is_symbol);
  mu_run_test(integration_test_is_nil);
  mu_run_test(integration_test_eq);
  mu_run_test(integration_test_AND);
  mu_run_test(integration_test_factorial);
  mu_run_test(integration_test_less);
  mu_run_test(integration_test_greater);
  mu_run_test(integration_test_division);
  mu_run_test(integration_test_OR);
  mu_run_test(integration_test_car);
  mu_run_test(integration_test_cdr);
  mu_run_test(integration_test_cons);
  return 0;
}

int main(int argc, char **argv) {
  const char *result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  } else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}