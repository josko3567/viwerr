long _viwerr_popcnt(
        long arg )
{

        int i, count;
        for(i = count = 0; i < (int)sizeof(long)*8; i++)
                if( (arg & (long)1<<i) != 0 )
                        count++;

        return count;

}