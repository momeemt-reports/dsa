#include "open_addressing.h"

DictOpenAddr *create_dict(int len) {
    DictOpenAddr *dict = (DictOpenAddr *)malloc(sizeof(DictOpenAddr));
    dict->B = len;
    dict->H = (DictData *)malloc(sizeof(DictData) * len);
    for (int i = 0; i < len; i++) {
        dict->H[i].name = -1;
        dict->H[i].state = EMPTY;
    }
    return dict;
}

int h(DictOpenAddr *dict, int d, int count) {
    int hash = d + count;
    return hash;
}

int g(DictOpenAddr *dict, int d, int count) {
    int hash = count * (HASH_TABLE_PRIME - (d % HASH_TABLE_PRIME) + 1);
    return hash;
}

void insert_hash(DictOpenAddr *dict, int d) {
    int count = 0;
    int hash = h(dict, d, count) % dict->B;
    int init_hash = hash;

    do {
        if (dict->H[hash].state != OCCUPIED) {
            dict->H[hash].name = d;
            dict->H[hash].state = OCCUPIED;
            return;
        }
        count++;
        hash = h(dict, d, count) % dict->B;
    } while (hash != init_hash);

    fprintf(stderr, "Dictionary is full!\n");
    return;
}

void insert_hash2(DictOpenAddr *dict, int d) {
    int count = 0;
    int hash = (h(dict, d, count) + g(dict, d, count)) % dict->B;
    int init_hash = hash;

    do {
        if (dict->H[hash].state != OCCUPIED) {
            dict->H[hash].name = d;
            dict->H[hash].state = OCCUPIED;
            return;
        }
        count++;
        hash = (h(dict, d, count) + g(dict, d, count)) % dict->B;
    } while (hash != init_hash);

    fprintf(stderr, "Dictionary is full!\n");
    return;
}

int search_hash(DictOpenAddr *dict, int d) {
    int count = 0;
    int hash = h(dict, d, count) % dict->B;
    int init_hash = hash;

    do {
        if (dict->H[hash].state == OCCUPIED && dict->H[hash].name == d) {
            return hash;
        }
        count++;
        hash = h(dict, d, count) % dict->B;
    } while (hash != init_hash);

    return -1;
}

int search_hash2(DictOpenAddr *dict, int d) {
    int count = 0;
    int hash = (h(dict, d, count) + g(dict, d, count)) % dict->B;
    int init_hash = hash;

    do {
        if (dict->H[hash].state == OCCUPIED && dict->H[hash].name == d) {
            return hash;
        }
        count++;
        hash = (h(dict, d, count) + g(dict, d, count)) % dict->B;
    } while (hash != init_hash);

    return -1;
}

void delete_hash(DictOpenAddr *dict, int d) {
    int hash = search_hash(dict, d);
    if (hash == -1) {
        return;
    }
    dict->H[hash].state = DELETED;
}

void delete_hash2(DictOpenAddr *dict, int d) {
    int hash = search_hash2(dict, d);
    if (hash == -1) {
        return;
    }
    dict->H[hash].state = DELETED;
}

void dict_open_addr_to_string(DictOpenAddr *dict, char *str) {
    char *tmp = (char *)malloc(sizeof(char) * 100);
    sprintf(tmp, "DictOpenAddr: ");
    for (int i = 0; i < (int)dict->B; i++) {
        if (dict->H[i].state == OCCUPIED) {
            sprintf(tmp, "%s%d ", tmp, dict->H[i].name);
        } else if (dict->H[i].state == DELETED) {
            sprintf(tmp, "%sd ", tmp);
        } else {
            sprintf(tmp, "%se ", tmp);
        }
    }
    sprintf(str, "%s", tmp);
    free(tmp);
}

void display_dict_open_addr(DictOpenAddr *dict) {
    char *str = (char *)malloc(sizeof(char) * 100);
    dict_open_addr_to_string(dict, str);
    printf("DictOpenAddr:\n%s\n", str);
    free(str);
}

void delete_dict(DictOpenAddr *dict) {
    free(dict->H);
    dict->H = NULL;
    free(dict);
    dict = NULL;
    printf("Directiry deleted!\n");
}

// // ハッシュテーブルを作成する
// HashTable *create_hash_table(HashTableType type, int size) {
//     HashTable *table = (HashTable *)malloc(sizeof(HashTable));
//     table->type = type;
//     table->size = size;
//     table->prime = HASH_TABLE_PRIME;
//     table->items = (HashItem *)malloc(sizeof(HashItem) * size);
//     for (int i = 0; i < size; i++) {
//         table->items[i].data = -1;
//         table->items[i].state = EMPTY;
//     }
//     printf("HashTable created!\n");
//     return table;
// }

// // ハッシュテーブルのサイズを元にハッシュ値を計算する
// unsigned int hash_by_size(HashTable *table, int data) {
//     return data % table->size;
// }

// // ハッシュテーブルが持つ素数を元にハッシュ値を計算する
// unsigned int hash_by_prime(HashTable *table, int data) {
//     return table->prime - (data % table->prime) + 1;
// }

// // 線形探索法によるハッシュ値の計算
// // ハッシュ値が計算できない場合は`-1`を返す
// int liner_probing_hash(HashTable *table, int data) {
//     unsigned int hash = hash_by_size(table, data);
//     unsigned int init_hash = hash;
//     do {
//         if (table->items[hash].state != OCCUPIED) {
//             return hash;
//         }
//         hash = (hash + 1) % table->size;
//     } while (hash != init_hash);
//     return -1;
// }

// // 二重ハッシュ法によるハッシュ値の計算
// // ハッシュ値が計算できない場合には`-1`を返す
// int double_hashing_hash(HashTable *table, int data) {
//     unsigned int hash = hash_by_size(table, data);
//     unsigned int step = hash_by_prime(table, data);
//     unsigned int init_hash = hash;
//     do {
//         if (table->items[hash].state != OCCUPIED) {
//             return hash;
//         }
//         hash = (hash + step) % table->size;
//     } while (hash != init_hash);
//     return -1;
// }

// // ハッシュテーブルからハッシュ値を計算する
// int calc_hash(HashTable *table, int data) {
//     int hash = -1;
//     switch (table->type) {
//         case LINEAR_PROBING:
//             hash = liner_probing_hash(table, data);
//             break;
//         case DOUBLE_HASHING:
//             hash = double_hashing_hash(table, data);
//             break;
//         default:
//             fprintf(stderr, "Invalid HashTableType\n");
//             return -1;
//     }
//     if (hash == -1) {
//         // fprintf(stderr, "HashTable is full\n");
//         return -1;
//     }
//     return hash;
// }

// // ハッシュテーブルにデータを挿入する
// void insert_hash(HashTable *table, int data) {
//     int hash = calc_hash(table, data);
//     if (hash == -1) {
//         return;
//     }
//     table->items[hash].data = data;
//     table->items[hash].state = OCCUPIED;
//     return;
// }

// // ハッシュテーブルからデータを探索する
// int search_hash(HashTable *table, int data) {
//     int hash = calc_hash(table, data);
//     if (hash == -1) {
//         return -1;
//     }
//     if (table->items[hash].state != OCCUPIED) {
//         return -1;
//     }
//     return hash;
// }

// // ハッシュテーブルからデータを削除する
// void delete_hash(HashTable *table, int data) {
//     int hash = search_hash(table, data);
//     if (hash == -1) {
//         return;
//     }
//     table->items[hash].state = DELETED;
//     return;
// }

// // ハッシュテーブルを表示する
// void display_hash(HashTable *table) {
//     printf("Hash table:\n");
//     for (int i = 0; i < (int)table->size; i++) {
//         if (table->items[i].state == OCCUPIED) {
//             printf("%d ", table->items[i].data);
//         } else if (table->items[i].state == DELETED) {
//             printf("d ");
//         } else {
//             printf("e ");
//         }
//     }
//     printf("\n");
// }

// // ハッシュテーブルを削除する
// void delete_hash_table(HashTable *table) {
//     free(table->items);
//     free(table);
//     printf("Hash table deleted!\n");
// }
