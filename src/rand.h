int random_bool(double p)
{
    double tmp = (rand() % 99)/100.0;
    if (tmp >= 1-p)
        return 1;
    else
        return 0;
}
