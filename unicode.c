if ((bit == 8 && k == 0) || (bit == 16 && k == 2) || (bit == 24 && k == 3) || (bit == 32 && k == 4))
        count++;
    if (bit == 32 && k == 4)
    {
        write(1, c, 4);
        // write(1, "2", 1);
        c[0] = 0;
        c[1] = 0;
        c[2] = 0;
        c[3] = 0;
        bit = 0;
        k = 0;
    }
    if (bit == 24 && k == 3)
    {
        write(1, c, 3);
        // write(1, "3", 1);
        c[0] = 0;
        c[1] = 0;
        c[2] = 0;
        bit = 0;
        k = 0;
    }
    if (bit == 16 && k == 2)
    {
        write(1,  &c, 2);
        // write(1, "1", 1);
        c[0] = 0;
        c[1] = 0;
        bit = 0;
        k = 0;
    }
    if (bit == 8 && k == 0)
    {
        // write(1, "0", 1);
        write(1, c, 1);
        c[0] = 0;
        bit = 0;
    }
}