// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "jobs.h"
#include "scheduler.h"

int counter = 0;

void add(int time)
{
    for (int t = 0; t < time; t++)
    {
        counter += 3;
    }
}

void mult(int time)
{
    for (int t = 0; t < time; t++)
    {
        counter *= 3;
    }
}

void reset(int time)
{
    for (int t = 0; t < time; t++)
    {
        counter = 1;
    }
}

void divide(int time)
{
    for (int t = 0; t < time; t++)
    {
        counter /= 2;
    }
}

void subtract(int time)
{
    for (int t = 0; t < time; t++)
    {
        counter -= 2;
    }
}

void test(int* n_jobs, Job** jobs)
{
    *n_jobs = 5;

    Job* example_jobs = (Job*)malloc((*n_jobs)*sizeof(Job));
    int priority[5] = {0,1,1,1,0};
    int time[5] = {3,2,4,3,1};
    Operation ops[5] = {add, mult, reset, subtract, divide};
    for (int i = 0; i < *n_jobs; i++)
    {
        example_jobs[i].priority = priority[i];
        example_jobs[i].idx = i;
        example_jobs[i].time = time[i];
        example_jobs[i].run_job = ops[i];
    }
    *jobs = example_jobs;
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(SchedulerTest, TestsIntests)
{
    int n_jobs;
    Job* jobs;
   
    test(&n_jobs, &jobs);
    counter = 0;
    priority(n_jobs, jobs);
    assert(counter == -5);
    free(jobs);
}
