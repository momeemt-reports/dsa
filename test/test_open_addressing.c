#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "open_addressing.h"
#include "timer.h"

void open_addressing_test_1(void);
void open_addressing_test_2(void);
void open_addressing_test_3(void);
void open_addressing_test_4(void);
void open_addressing_test_5(void);
void open_addressing_test_6(void);
void open_addressing_test_7(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite open_addressing_suite =
        CU_add_suite("Open Addressing Test", NULL, NULL);
    if (open_addressing_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(open_addressing_suite, "Open_Addressing_Test_1",
                open_addressing_test_1);
    CU_add_test(open_addressing_suite, "Open_Addressing_Test_2",
                open_addressing_test_2);
    CU_add_test(open_addressing_suite, "Open_Addressing_Test_3",
                open_addressing_test_3);
    CU_add_test(open_addressing_suite, "Open_Addressing_Test_4",
                open_addressing_test_4);
    CU_add_test(open_addressing_suite, "Open_Addressing_Test_5",
                open_addressing_test_5);
    CU_add_test(open_addressing_suite, "Open_Addressing_Test_6",
                open_addressing_test_6);
    CU_add_test(open_addressing_suite, "Open_Addressing_Test_7",
                open_addressing_test_7);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

void open_addressing_test_1(void) {
    DictOpenAddr *dict = create_dict(10);
    insert_hash(dict, 1);

    CU_ASSERT_EQUAL(dict->H[1].name, 1);
    CU_ASSERT_EQUAL(dict->H[1].state, OCCUPIED);

    delete_dict(dict);
}

void open_addressing_test_2(void) {
    DictOpenAddr *dict = create_dict(10);
    insert_hash(dict, 1);

    int hash = search_hash(dict, 1);

    CU_ASSERT_EQUAL(hash, 1);

    delete_dict(dict);
}

void open_addressing_test_3(void) {
    DictOpenAddr *dict = create_dict(10);
    insert_hash(dict, 1);

    int hash = search_hash(dict, 2);

    CU_ASSERT_EQUAL(hash, -1);

    delete_dict(dict);
}

void open_addressing_test_4(void) {
    DictOpenAddr *dict = create_dict(10);
    insert_hash(dict, 1);
    insert_hash(dict, 11);

    CU_ASSERT_EQUAL(dict->H[1].name, 1);
    CU_ASSERT_EQUAL(dict->H[1].state, OCCUPIED);
    CU_ASSERT_EQUAL(dict->H[2].name, 11);
    CU_ASSERT_EQUAL(dict->H[2].state, OCCUPIED);

    delete_dict(dict);
}

void open_addressing_test_5(void) {
    DictOpenAddr *dict = create_dict(10);
    insert_hash(dict, 1);
    insert_hash(dict, 11);

    int hash = search_hash(dict, 1);

    CU_ASSERT_EQUAL(hash, 1);

    hash = search_hash(dict, 11);

    CU_ASSERT_EQUAL(hash, 2);

    delete_dict(dict);
}

void open_addressing_test_6(void) {
    DictOpenAddr *dict = create_dict(10);
    for (int i = 1; i <= 10; i++) {
        insert_hash(dict, i);
    }

    insert_hash(dict, 11);

    delete_dict(dict);
}

void open_addressing_test_7(void) {
    const int TABLE_SIZE = 999983;
    const int TRY_NUMBER = 5;
    const int RANDOM_SEED = 19;
    Timer *timer = new_timer();

    int *data = (int *)malloc(sizeof(int) * TABLE_SIZE);
    srand(RANDOM_SEED);
    for (int i = 0; i < TABLE_SIZE; i++) {
        data[i] = rand();
    }

    double *liner_time_data = (double *)malloc(sizeof(double) * 11);
    double *double_time_data = (double *)malloc(sizeof(double) * 11);

    for (int alpha = 0; alpha <= 10; alpha++) {
        DictOpenAddr *liner_table = create_dict(TABLE_SIZE);
        DictOpenAddr *double_table = create_dict(TABLE_SIZE);

        for (int i = 0; i < TABLE_SIZE * alpha / 10; i++) {
            int datum = data[i];
            insert_hash(liner_table, datum);
            insert_hash2(double_table, datum);
        }

        double liner_time = 0.0;
        double double_time = 0.0;
        for (int try = 0; try < TRY_NUMBER; try++) {
            timer->reset(timer);
            timer->start(timer);
            for (int i = 0; i < TABLE_SIZE * alpha / 10; i++) {
                search_hash(liner_table, data[i]);
            }
            timer->stop(timer);
            liner_time += timer->result(timer);

            timer->reset(timer);
            timer->start(timer);
            for (int i = 0; i < TABLE_SIZE * alpha / 10; i++) {
                search_hash2(double_table, data[i]);
            }
            timer->stop(timer);
            double_time += timer->result(timer);
        }
        liner_time /= TRY_NUMBER;
        double_time /= TRY_NUMBER;

        liner_time_data[alpha] = liner_time;
        double_time_data[alpha] = double_time;

        delete_dict(liner_table);
        delete_dict(double_table);
    }

    char *now = (char *)malloc(sizeof(char) * 20);
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(now, 20, "%Y%m%d%H%M%S", tm);

    FILE *gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set terminal jpeg size 1024,512\n");
    fprintf(gp, "set output \"./test/graph/open_addressing_%s.jpeg\"\n", now);
    fprintf(gp,
            "set multiplot layout 1,2 title \"Open Addressing Comparison\"\n");

    fprintf(gp, "set title \"Linear Scale\"\n");
    fprintf(gp, "set xlabel \"alpha\"\n");
    fprintf(gp, "set ylabel \"time [usec]\"\n");
    fprintf(gp, "set xrange [0:1]\n");
    fprintf(gp, "set yrange [0:*]\n");
    fprintf(gp, "set size square\n");
    fprintf(gp,
            "plot '-' with lines title \"linear\", '-' with lines title "
            "\"double\"\n");

    for (int alpha = 0; alpha <= 10; alpha++) {
        fprintf(gp, "%f %lf\n", (double)alpha / 10.0,
                liner_time_data[alpha] * 1000000);
        printf("%d %.15g\n", alpha, liner_time_data[alpha] * 1000000);
    }
    fprintf(gp, "e\n");

    for (int alpha = 0; alpha <= 10; alpha++) {
        fprintf(gp, "%f %lf\n", (double)alpha / 10.0,
                double_time_data[alpha] * 1000000);
        printf("%d %.15g\n", alpha, double_time_data[alpha] * 1000000);
    }
    fprintf(gp, "e\n");

    fprintf(gp, "set title \"Logarithmic Scale\"\n");
    fprintf(gp, "set logscale y\n");
    fprintf(gp, "set xlabel \"alpha\"\n");
    fprintf(gp, "set ylabel \"time [usec]\"\n");
    fprintf(gp, "set xrange [0:1]\n");
    fprintf(gp, "set yrange [*:*]\n");
    fprintf(gp, "set size square\n");
    fprintf(gp,
            "plot '-' with lines title \"linear\", '-' with lines title "
            "\"double\"\n");

    for (int alpha = 0; alpha <= 10; alpha++) {
        if (liner_time_data[alpha] > 0) {
            fprintf(gp, "%f %lf\n", (double)alpha / 10.0,
                    liner_time_data[alpha] * 1000000);
        }
    }
    fprintf(gp, "e\n");

    for (int alpha = 0; alpha <= 10; alpha++) {
        if (double_time_data[alpha] > 0) {
            fprintf(gp, "%f %lf\n", (double)alpha / 10.0,
                    double_time_data[alpha] * 1000000);
        }
    }
    fprintf(gp, "e\n");

    fprintf(gp, "unset multiplot\n");
    fflush(gp);
    pclose(gp);
}
