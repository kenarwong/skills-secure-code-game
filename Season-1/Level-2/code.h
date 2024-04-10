// Welcome to Secure Code Game Season-1/Level-2!

// Follow the instructions below to get started:

// 1. Perform code review. Can you spot the bug? 
// 2. Run tests.c to test the functionality
// 3. Run hack.c and if passing then CONGRATS!
// 4. Compare your solution with solution.c

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 39
#define SETTINGS_COUNT 10
#define MAX_USERS 100
#define INVALID_USER_ID -1

// For simplicity, both the private (implementation specific) and the public (API) parts 
// of this application have been combined inside this header file. In the real-world, it
// is expected for the public (API) parts only to be presented here. Therefore, for the 
// purpose of this level, please assume that the private (implementation specific) sections 
// of this file, would not be known to the non-privileged users of this application

// Internal counter of user accounts
int userid_next = 0;

// The following structure is implementation-speicific and it's supposed to be unknown 
// to non-privileged users
typedef struct {
    bool isAdmin; // 8
    long userid; // 8
    char username[MAX_USERNAME_LEN + 1]; // 40
    long setting[SETTINGS_COUNT]; // 80
} user_account;

// Simulates an internal store of active user accounts
user_account *accounts[MAX_USERS];

// The signatures of the following four functions together with the previously introduced 
// constants (see #DEFINEs) constitute the API of this module

// Creates a new user account and returns it's unique identifier
int create_user_account(bool isAdmin, const char *username) {
    if (userid_next >= MAX_USERS) {
        fprintf(stderr, "the maximum number of users have been exceeded");
        return INVALID_USER_ID;
    }    

    user_account *ua;
    if (strlen(username) > MAX_USERNAME_LEN) {
        fprintf(stderr, "the username is too long");
        return INVALID_USER_ID;
    }    

    printf("size of user_account %zu\n", sizeof(user_account));

    ua = malloc(sizeof (user_account));
    if (ua == NULL) {
        fprintf(stderr, "malloc failed to allocate memory");
        return INVALID_USER_ID;
    }
    ua->isAdmin = isAdmin;
    ua->userid = userid_next++;
    strcpy(ua->username, username);
    // Better way
    // Ensure properly null-terminated
    // memset(ua->username, 0, MAX_USERNAME_LEN + 1);
    // Use strncpy to specify max number of characters to copy from source. This prevents buffer overflows.
    // strncpy(ua->username, username, MAX_USERNAME_LEN);
    // username[MAX_USERNAME_LEN] = '\0'; // Ensure null terminator when using strncpy

    memset(&ua->setting, 0, sizeof ua->setting);
    accounts[userid_next] = ua;
    return userid_next++;
}

// Updates the matching setting for the specified user and returns the status of the operation
// A setting is some arbitrary string associated with an index as a key
bool update_setting(int user_id, const char *index, const char *value) {
    if (user_id < 0 || user_id >= MAX_USERS)
        return false;

    char *endptr;
    long i, v;
    printf("index: %s\n", index);
    i = strtol(index, &endptr, 10);
    printf("long conversion: %ld\n", i);

    if (*endptr) // Should be null \0 after long conversion 
        return false;

    v = strtol(value, &endptr, 10);
    if (*endptr || i < 0 || i >= SETTINGS_COUNT) // Do not allow negative index keys
        return false;
    accounts[user_id]->setting[i] = v; 
    return true;
}

// Returns whether the specified user is an admin
bool is_admin(int user_id) {
    if (user_id < 0 || user_id >= MAX_USERS) {
        fprintf(stderr, "invalid user id");
        return false;
    }    
    return accounts[user_id]->isAdmin;
}

// Returns the username of the specified user
const char* username(int user_id) {
    // Returns an error for invalid user ids
    if (user_id < 0 || user_id >= MAX_USERS) {
        fprintf(stderr, "invalid user id");
        return NULL;
    }    
    return accounts[user_id]->username;
}