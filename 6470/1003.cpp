int *sort(const int *const array, int size)
{
    if (size <= 1)
    {
        int *buf = new int;
        *buf = *array;
        return buf;
    }
    else
    {
        int r = size / 2;
        // recursion
        int *left = sort(array, r);
        int *right = sort(array + r, size - r);

        int *buffer = new int[size];
        for (int lp = 0, lq = 0, curr = 0; curr < size; curr++)
        {
            if (lp < r && lq < size - r)
            {
                if (left[lp] <= right[lq])
                {
                    buffer[curr] = left[lp++];
                }
                else
                {
                    buffer[curr] = right[lq++];
                }
            }
            else
            {
                if (lp >= r)
                {
                    buffer[curr] = right[lq++];
                }
                else if (lq >= size - r)
                {
                    buffer[curr] = left[lp++];
                }
            }
        }
        // clean up
        delete left;
        delete right;
        // return sorted
        return buffer;
    }
}
