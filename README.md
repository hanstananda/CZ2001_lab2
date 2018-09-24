# CZ2001_lab2

## Howto Run 

### Closed address hashing

Compile and run the `Lab2_closed_address_hashing.c`. It will then automatically run the provided test cases. To test it manually, comment every lines that has `freeopen` command(49,50,101). 

Test cases has been generated on `Random_tc_generated_load75%.txt` for the initial list of students to be put on the hashtable. 

For the query, it has also been generated in `Random_query_generated.txt`. This textfile contains 100000 random queries that is taken from list of people from the initial list.

### Test case generator notes
- Just rename the freeopen stdout part with anything and play with it. 
- The random query generator need to be set whether the list of people will be taken from the initial generated query or not. This can be done by modifying the `bool successful` value.  

## Notes
Initial name seed generated from: https://www.randomlists.com/random-names
