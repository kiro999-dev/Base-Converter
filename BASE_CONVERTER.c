#include <stdio.h>
#include <stdlib.h>

// Function to calculate the length of a string
int ft_strlen(char *str) {
    int i = 0;
    while (str[i]) {
        i++;
    }
    return i;
}

// Function to check if a character is present in a given base
int its_in_base(char c, char *base) {
    int i = 0;
    
    while (base[i]) {
        if (c == base[i]) {
            return 1;  // Character found in the base
        }
        i++;
    }
    return 0;  // Character not found in the base
}

// Function to find the index of a character in a given base
int ft_index(char c, char *base) {
    int i = 0;
    while (base[i] != c && base[i]) {
        i++;
    }
    return i;
}

// Function to check for errors in the input
int check_error(char *str) {
    int i = 0;
    int count[256] = {0};

    if (str[i] == '\0' || ft_strlen(str) == 1) {
        return 0;
    }

    while (str[i++]) {
        if (str[i] == '-' || str[i] == '+') {
            return 0;
        }
    }

    i = 0;
    while (str[i]) {
        if (count[(int)str[i] - 48] == 1) {
            return 0;
        }
        count[(int)str[i++] - 48]++;
    }

    return 1;
}

// Function to handle whitespaces in the input
int whitespaces(char *str, int *ptr_i) {
    int i = 0;
    int signe = 1;

    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32) {
        i++;
    }

    while (str[i] == '-' || str[i] == '+') {
        if (str[i++] == '-') {
            signe *= -1;
        }
    }

    *ptr_i = i;
    return signe;
}

// Function to convert a number from a given base to decimal
long long int ft_convert_base_from(char *str, char *base) {
    int cheak = check_error(base);
    int sign, result, len_base, i;
    long long nbr;

    if (!cheak) {
        return 0;
    }

    len_base = ft_strlen(base);
    sign = whitespaces(str, &i);
    result = 0;
    
    while (str[i] && its_in_base(str[i], base)) {
        nbr = ft_index(str[i], base);
        if (nbr == -1) {
            break;
        }
        result *= len_base;
        result = result + nbr;
        i++;
    }

    result *= sign;

    return result;
}

// Function to convert a decimal number to a given base
char *ft_convert_base_to(int nbr, char *base_to, char *result, int len_base) {
    int j = 0;
    int sign = 0;
    int cpy_nbr = abs(nbr);

    if (nbr < 0) {
        sign = 1;
    }

    while (cpy_nbr != 0) {
        j++;
        cpy_nbr = cpy_nbr / len_base;
    }

    result[j] = '\0';

    if (sign) {
        j++;
        result[0] = '-';
    }

    while (nbr != 0) {
        result[--j] = base_to[abs(nbr) % len_base];
        nbr = nbr / len_base;
    }

    return result;
}

// Function to convert a number from one base to another
char *ft_convert_base(char *nbr, char *base_from, char *base_to) {
    int check = check_error(base_to);
    if (!check) {
        return NULL;
    }

    // Convert the input number to decimal
    long long int nbr_n = ft_convert_base_from(nbr, base_from);
    int len_base = ft_strlen(base_to);

    // Allocate memory for the result string
    char *nbr_str = malloc(64);
    
    // Convert the decimal number to the target base
    char *result = ft_convert_base_to(nbr_n, base_to, nbr_str, len_base);

    return result;
}

// Main function for testing the conversion functions
int main() {
    // Test cases
    char *str = ft_convert_base("-12aac", "0123456789", "01");
    char *str2 = ft_convert_base("1111111111111011111111111111", "01", "0123456789abcdef");
    char *str3 = ft_convert_base("fffaae", "0123456789abcdef", "0123456789");
    char *str4 = ft_convert_base("fffffff", "0123456789abcdef", "01234567");

    // Print the results
    printf("Binary: %s\n", str);
    printf("Hexadecimal: %s\n", str2);
    printf("Decimal: %s\n", str3);
    printf("Octal: %s\n", str4);

    // Free allocated memory
    free(str);
    free(str2);
    free(str3);
    free(str4);

    return 0;
}

