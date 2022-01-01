#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

// --- 

/*
algorithm explanation for later reference:
- David’s Visa: 4003600000000014
- 1•2 + 0•2 + 0•2 + 0•2 + 0•2 + 6•2 + 0•2 + 4•2
- That gives us:
    2 + 0 + 0 + 0 + 0 + 12 + 0 + 8
- Now let’s add those products’ digits (i.e., not the products themselves) together:
    2 + 0 + 0 + 0 + 0 + 1 + 2 + 0 + 8 = 13
- Now let’s add that sum (13) to the sum of the digits that weren’t multiplied (from the end):
    13 + 4 + 0 + 0 + 0 + 0 + 0 + 3 + 0 = 20
--> the last digit in that sum (20) is a 0, so David’s card is legit!
*/

// set testing to true if you want to run tests below
const bool TEST_RUN = false;
// set loggint to true for development or understanding the code
const bool LOGGING = false;

string get_cc_type(long card_number);

int main(void)
{
    if (TEST_RUN)
    {
        void run_tests(void);
        run_tests();
    }
    else
    {
        long card_number = get_long("Enter your credit card number: ");

        string credit_card_type = get_cc_type(card_number);
        printf("%s\n", credit_card_type);
    }

    return 0;
}

string get_cc_type(long card_number)
{
    int get_number_len(long value);
    int card_number_len = get_number_len(card_number);

    // if a card number has the wrong length, we return INVALID right away
    if (card_number_len > 16 || card_number_len < 13)
    {
        return "INVALID";
    }

    // check if the checksum is valid
    int is_cc_checksum_valid(long card_number, int card_number_len);
    int checksum_valid = is_cc_checksum_valid(card_number, card_number_len);

    // if the checksum is valid, determine what type of card it is
    if (checksum_valid)
    {
        // get first two numbers of card
        while (card_number > 100) 
        {
            card_number /= 10;
        }

        // if the card's first 2 numbers start with 4x (card starts with 4), keep only 4
        if (card_number > 39 && card_number < 50)
        {
            card_number = 4;
        }
        LOGGING &&printf("card_number after /= 10: %li\n", card_number);
        LOGGING &&printf("card_number_len: %i\n", card_number_len);

        // match the card number and its initial length to the correct credit card type
        switch (card_number)
        {
            case 34:
            case 37:
                return card_number_len == 15
                       ? "AMEX"
                       : "INVALID";
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                return card_number_len == 16
                       ? "MASTERCARD"
                       : "INVALID";
            case 4:
                return card_number_len == 13 || card_number_len == 16
                       ? "VISA"
                       : "INVALID";
            default:
                return "INVALID";
        }
    }
    else
    {
        return "INVALID";
    }
}

int is_cc_checksum_valid(long card_number, int card_number_len)
{
    // split card long into two ints for processing
    int every = 0;
    int every_other = 0;

    for (int i = 0; i < card_number_len; i++)
    {
        int last_int = card_number % 10;
        if (i % 2 == 0)
        {
            every = every * 10 + last_int;
        }
        else 
        {
            every_other = every_other * 10 + last_int;
        }
        card_number /= 10;
    }
    LOGGING &&printf("------\n");
    LOGGING &&printf("every: %i\n", every);
    LOGGING &&printf("every_other: %i\n", every_other);

    // multiply each in every_other by 2 and add each product
    long every_other_squared = 0;
    for (int i = 0; i < ceil(card_number_len / 2); i++) 
    {
        int next_other_squared = every_other % 10 * 2;
        while (next_other_squared)
        {
            every_other_squared = every_other_squared * 10 + next_other_squared % 10;
            next_other_squared /= 10;
        }
        every_other /= 10;
    }
    LOGGING &&printf("every_other_squared: %li\n", every_other_squared);

    // sum every and every_other_squared
    int sum = 0;
    while (every)
    {
        sum += every % 10;
        every /= 10;
    }
    while (every_other_squared)
    {
        sum += every_other_squared % 10;
        every_other_squared /= 10;
    }

    // return the check if the sum is dividable by 10
    bool is_valid = sum % 10 == 0;
    LOGGING &&printf("result: %d\n", is_valid);
    return is_valid;
}

int get_number_len(long value)
{
    int l = 1;
    while (value > 9)
    {
        l++; 
        value /= 10; 
    }
    return l;
}

// tests (activatable above)

void run_tests(void)
{
    printf("%i: 378282246310005 == AMEX\n", strcmp(get_cc_type(378282246310005), "AMEX") == 0);
    printf("%i: 371449635398431 == AMEX\n", strcmp(get_cc_type(371449635398431), "AMEX") == 0);
    printf("%i: 5555555555554444 == MC\n", strcmp(get_cc_type(5555555555554444), "MASTERCARD") == 0);
    printf("%i: 5105105105105100 == MC\n", strcmp(get_cc_type(5105105105105100), "MASTERCARD") == 0);
    printf("%i: 4111111111111111 == VISA\n", strcmp(get_cc_type(4111111111111111), "VISA") == 0);
    printf("%i: 4012888888881881 == VISA\n", strcmp(get_cc_type(4012888888881881), "VISA") == 0);
    printf("%i: 4222222222222 == VISA\n", strcmp(get_cc_type(4222222222222), "VISA") == 0);
    printf("%i: 1234567890 == -\n", strcmp(get_cc_type(1234567890), "INVALID") == 0);
    printf("%i: 369421438430814 == -\n", strcmp(get_cc_type(369421438430814), "INVALID") == 0);
    printf("%i: 4062901840 == -\n", strcmp(get_cc_type(4062901840), "INVALID") == 0);
    printf("%i: 5673598276138003 == -\n", strcmp(get_cc_type(5673598276138003), "INVALID") == 0);
    printf("%i: 4111111111111113 == -\n", strcmp(get_cc_type(4111111111111113), "INVALID") == 0);
    printf("%i: 4222222222223 == -\n", strcmp(get_cc_type(4222222222223), "INVALID") == 0);
}

/*
compile and run it: "clang -lcs50 ./credit.c -o credit.out && ./credit.out"
check it: check50 cs50/problems/2022/x/credit
submit it: submit50 cs50/problems/2022/x/credit
*/
