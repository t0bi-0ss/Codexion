void compile(long id, int compilations)
{
    printf("Coder n: %ld has compiled effectively for the %d time\n", id, compilations + 1);
    usleep(100000);
}

void debug(long id)
{
    printf("Coder n: %ld is debugging\n", id);
}

void refactor(long id)
{
    printf("Coder n: %ld is refactoring\n", id);
}