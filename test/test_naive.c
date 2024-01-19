#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "naive.h"

void naive_test_matching();
void naive_test_mismatch();
void naive_survey_cmp_count();

int main(void) {
    CU_initialize_registry();

    CU_pSuite naive_suite = CU_add_suite("naive Test", NULL, NULL); 
    if (naive_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(naive_suite, "naive_Test_Matching", naive_test_matching);
    CU_add_test(naive_suite, "naive_Test_Mismatch", naive_test_mismatch);

    naive_survey_cmp_count();

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
        text[i] = rand() % 26 + 'a';
    }
    text[textlen] = '\0';
}

void naive_survey_cmp_count() {
    const int MAX_TEXT_LENGTH = 1000;
    const int MAX_PAT_LENGTH = 100;
    int cmp_count_data[MAX_TEXT_LENGTH][MAX_PAT_LENGTH];
    
    char text[MAX_TEXT_LENGTH + 1];
    char pat[MAX_PAT_LENGTH + 1];
    random_text(MAX_TEXT_LENGTH, text);
    random_text(MAX_PAT_LENGTH, pat);

    for (int textlen = 1; textlen <= MAX_TEXT_LENGTH; textlen++) {
        for (int patlen = 1; patlen <= MAX_PAT_LENGTH; patlen++) {
            reset_Ncmp();
            naive(text, textlen, pat, patlen);
            cmp_count_data[textlen - 1][patlen - 1] = Ncmp;
        }
    }

    // 二次元散布図を描画する
    FILE *gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set xlabel \"text length\"\n");
    fprintf(gp, "set ylabel \"pattern length\"\n");
    fprintf(gp, "set zlabel \"cmp count\"\n");
    fprintf(gp, "set xrange [1:1000]\n");
    fprintf(gp, "set yrange [1:100]\n");
    fprintf(gp, "set dgrid3d 50,50\n");
    fprintf(gp, "set hidden3d\n");
    fprintf(gp, "set ticslevel 0\n");
    fprintf(gp, "set pm3d\n");
    fprintf(gp, "set palette rgbformulae 33,13,10\n");
    fprintf(gp, "set terminal jpeg size 1024,512\n");
    fprintf(gp, "set output \"./test/graph/naive_cmp_count.jpeg\"\n");
    fprintf(gp, "splot '-' with lines\n");
    for (int textlen = 1; textlen <= MAX_TEXT_LENGTH; textlen++) {
        for (int patlen = 1; patlen <= MAX_PAT_LENGTH; patlen++) {
            fprintf(gp, "%d %d %d\n", textlen, patlen, cmp_count_data[textlen - 1][patlen - 1]);
        }
        fprintf(gp, "\n");
    }
    fprintf(gp, "e\n");
    fflush(gp);
    fclose(gp);

}
