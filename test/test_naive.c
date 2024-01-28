#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "naive.h"
#include "kmp.h"

void naive_test_matching();
void naive_test_mismatch();
void survey_cmp_count();
void survey_cmp_count_all_alphabet();
void survey_cmp_count_worst_case();

int main(void) {
    CU_initialize_registry();

    CU_pSuite naive_suite = CU_add_suite("naive Test", NULL, NULL); 
    if (naive_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(naive_suite, "naive_Test_Matching", naive_test_matching);
    CU_add_test(naive_suite, "naive_Test_Mismatch", naive_test_mismatch);

    survey_cmp_count();
    survey_cmp_count_all_alphabet();
    survey_cmp_count_worst_case();

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

bool isVerbose = false;
int Ncmp = 0;

void reset_Ncmp() {
    Ncmp = 0;
}

void naive_test_matching() {
    char* text = "This is a pen.";
    char* pat = "pen";
    int textlen = strlen(text);
    int patlen = strlen(pat);
    int result = naive(text, textlen, pat, patlen);
    CU_ASSERT_EQUAL(result, 10);
}

void naive_test_mismatch() {
    char *text = "This is a pen.";
    char *pat = "ix";
    int textlen = strlen(text);
    int patlen = strlen(pat);
    int result = naive(text, textlen, pat, patlen);
    CU_ASSERT_EQUAL(result, -1);
}

void random_text(int textlen, char *text) {
    for (int i = 0; i < textlen; i++) {
        text[i] = rand() % 2 + 'a';
    }
    text[textlen] = '\0';
}

void random_text_all_alphabet(int textlen, char *text) {
    for (int i = 0; i < textlen; i++) {
        text[i] = rand() % 26 + 'a';
    }
    text[textlen] = '\0';
}

void survey_cmp_count() {
    const int MAX_TEXT_LENGTH = 10000;
    const int PAT_LENGTH = 30;

    const int SEED = 19;
    srand(SEED);
    
    char text[MAX_TEXT_LENGTH + 1];
    char pat[PAT_LENGTH + 1];
    random_text(MAX_TEXT_LENGTH, text);
    random_text(PAT_LENGTH, pat);

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        perror("Gnuplot pipe opening failed");
        return;
    }
    fprintf(gnuplotPipe, "set terminal jpeg\n");
    fprintf(gnuplotPipe, "set output 'test/graph/test_string_matching.jpeg'\n");
    fprintf(gnuplotPipe, "set title 'Comparison Counts'\n");
    fprintf(gnuplotPipe, "set xlabel 'Text Length'\n");
    fprintf(gnuplotPipe, "set ylabel 'Comparison Count'\n");
    fprintf(gnuplotPipe, "set key left top\n");
    fprintf(gnuplotPipe, "plot '-' using 1:2 title 'Naive' with points pointtype 7 linecolor 'red', \\\n");
    fprintf(gnuplotPipe, "'-' using 1:2 title 'KMP' with points pointtype 7 linecolor 'blue'\n");

    for (int textlen = 100; textlen <= MAX_TEXT_LENGTH; textlen += 100) {
        reset_Ncmp();
        naive(text, textlen, pat, PAT_LENGTH);
        fprintf(gnuplotPipe, "%d %d\n", textlen, Ncmp);

        if (textlen % 100 == 0) {
            printf("naive: textlen = %d, Ncmp = %d\n", textlen, Ncmp);
        }
    }
    fprintf(gnuplotPipe, "e\n");

    for (int textlen = 100; textlen <= MAX_TEXT_LENGTH; textlen += 100) {
        reset_Ncmp();
        kmp(text, textlen, pat, PAT_LENGTH);
        fprintf(gnuplotPipe, "%d %d\n", textlen, Ncmp);

        if (textlen % 100 == 0) {
            printf("kmp: textlen = %d, Ncmp = %d\n", textlen, Ncmp);
        }
    }
    fprintf(gnuplotPipe, "e\n");

    pclose(gnuplotPipe);
    fprintf(gnuplotPipe, "e\n");
    fprintf(gnuplotPipe, "e\n");
    pclose(gnuplotPipe);
}

void survey_cmp_count_all_alphabet() {
    const int MAX_TEXT_LENGTH = 10000;
    const int PAT_LENGTH = 30;

    const int SEED = 19;
    srand(SEED);
    
    char text[MAX_TEXT_LENGTH + 1];
    char pat[PAT_LENGTH + 1];
    random_text_all_alphabet(MAX_TEXT_LENGTH, text);
    random_text_all_alphabet(PAT_LENGTH, pat);

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        perror("Gnuplot pipe opening failed");
        return;
    }
    fprintf(gnuplotPipe, "set terminal jpeg\n");
    fprintf(gnuplotPipe, "set output 'test/graph/test_string_matching_all_alphabet.jpeg'\n");
    fprintf(gnuplotPipe, "set title 'Comparison Counts'\n");
    fprintf(gnuplotPipe, "set xlabel 'Text Length'\n");
    fprintf(gnuplotPipe, "set ylabel 'Comparison Count'\n");
    fprintf(gnuplotPipe, "set key left top\n");
    fprintf(gnuplotPipe, "plot '-' using 1:2 title 'Naive' with points pointtype 7 linecolor 'red', \\\n");
    fprintf(gnuplotPipe, "'-' using 1:2 title 'KMP' with points pointtype 7 linecolor 'blue'\n");

    for (int textlen = 100; textlen <= MAX_TEXT_LENGTH; textlen += 100) {
        reset_Ncmp();
        naive(text, textlen, pat, PAT_LENGTH);
        fprintf(gnuplotPipe, "%d %d\n", textlen, Ncmp);

        if (textlen % 100 == 0) {
            printf("naive: textlen = %d, Ncmp = %d\n", textlen, Ncmp);
        }
    }
    fprintf(gnuplotPipe, "e\n");

    for (int textlen = 100; textlen <= MAX_TEXT_LENGTH; textlen += 100) {
        reset_Ncmp();
        kmp(text, textlen, pat, PAT_LENGTH);
        fprintf(gnuplotPipe, "%d %d\n", textlen, Ncmp);

        if (textlen % 100 == 0) {
            printf("kmp: textlen = %d, Ncmp = %d\n", textlen, Ncmp);
        }
    }
    fprintf(gnuplotPipe, "e\n");

    pclose(gnuplotPipe);
    fprintf(gnuplotPipe, "e\n");
    fprintf(gnuplotPipe, "e\n");
    pclose(gnuplotPipe);
}

void worst_case_text(int textlen, char *text) {
    for (int i = 0; i < textlen; i++) {
        text[i] = 'a';
    }
    text[textlen] = '\0';
}

void survey_cmp_count_worst_case() {
    const int MAX_TEXT_LENGTH = 10000;
    const int PAT_LENGTH = 30;

    const int SEED = 19;
    srand(SEED);
    
    char text[MAX_TEXT_LENGTH + 1];
    char pat[PAT_LENGTH + 1];
    worst_case_text(MAX_TEXT_LENGTH, text);
    worst_case_text(PAT_LENGTH, pat);
    pat[PAT_LENGTH - 1] = 'b';

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        perror("Gnuplot pipe opening failed");
        return;
    }
    fprintf(gnuplotPipe, "set terminal jpeg\n");
    fprintf(gnuplotPipe, "set output 'test/graph/test_string_matching_worst_case.jpeg'\n");
    fprintf(gnuplotPipe, "set title 'Comparison Counts (Worst Case)'\n");
    fprintf(gnuplotPipe, "set xlabel 'Text Length'\n");
    fprintf(gnuplotPipe, "set ylabel 'Comparison Count'\n");
    fprintf(gnuplotPipe, "set key left top\n");
    fprintf(gnuplotPipe, "plot '-' using 1:2 title 'Naive' with points pointtype 7 linecolor 'red', \\\n");
    fprintf(gnuplotPipe, "'-' using 1:2 title 'KMP' with points pointtype 7 linecolor 'blue'\n");

    for (int textlen = 100; textlen <= MAX_TEXT_LENGTH; textlen += 100) {
        reset_Ncmp();
        naive(text, textlen, pat, PAT_LENGTH);
        fprintf(gnuplotPipe, "%d %d\n", textlen, Ncmp);

        if (textlen % 100 == 0) {
            printf("naive: textlen = %d, Ncmp = %d\n", textlen, Ncmp);
        }
    }
    fprintf(gnuplotPipe, "e\n");

    for (int textlen = 100; textlen <= MAX_TEXT_LENGTH; textlen += 100) {
        reset_Ncmp();
        kmp(text, textlen, pat, PAT_LENGTH);
        fprintf(gnuplotPipe, "%d %d\n", textlen, Ncmp);

        if (textlen % 100 == 0) {
            printf("kmp: textlen = %d, Ncmp = %d\n", textlen, Ncmp);
        }
    }
    fprintf(gnuplotPipe, "e\n");

    pclose(gnuplotPipe);
}
