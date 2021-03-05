/*******************************************************************************
 *   BRT Wallet
 *   (c) 2017 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#pragma once

#include <stdbool.h>

#include "os.h"
#include "cx.h"
#include "fields.h"

#define BRT_PUBKEY_SIZE  33
#define BRT_ADDRESS_SIZE 41

typedef struct {
    uint8_t buf[BRT_PUBKEY_SIZE];
} brt_pubkey_t;

typedef union {
    brt_pubkey_t pubkey;
    brt_account_t account;
} brt_pubkey_or_account;

typedef struct {
    char buf[BRT_ADDRESS_SIZE];
} brt_address_t;

void brt_public_key_hash160(brt_pubkey_t *pubkey, uint8_t *out);

size_t brt_public_key_to_encoded_base58(brt_pubkey_t *pubkey,
                                        brt_account_t *account,
                                        brt_address_t *out,
                                        uint16_t version);

void brt_compress_public_key(cx_ecfp_public_key_t *public_key, brt_pubkey_t *out);

void get_address(cx_ecfp_public_key_t *pubkey, brt_address_t *address);

int brt_print_amount(uint64_t amount, char *out, size_t outlen);

bool parse_bip32_path(uint8_t *path,
                      size_t path_length,
                      uint32_t *path_parsed,
                      size_t path_parsed_length);
