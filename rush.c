int check(char *str,int *arr)
{
    int i;
    int count;

    count = 0, i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '1' && str[i] <= '4')
        {
            arr[count] = str[i] -'0';
            count++;
        }
        else if (str[i] != ' ')
        {
            return (0);
        }
        i++;
    }
    if(count == 16)
    {
    return (1);
    }
    return (0);
}

void init_grid(int grid[4][4])
{
    int row;
    int col;

    row = 0;
    while (row < 4)
    {
        col = 0; //รีเซ็ตคอลัมน์กลับมาซ้ายสุดทุกครั้งที่ขึ้นแถวใหม่
        while (col < 4)
        {
            grid[row][col] = 0;
            col++;
        }
        row++;
    }
}

int check_double(int grid[4][4], int row, int col, int num)
{
    int i;

    i = 0;
    while (i < 4)
    {
        //ตรวจตัวซ้ำแนวนอน โดยทดลองใส่num = 3 ไปถ้าเท่ากัน พัง
        if (grid[row][i] == num)
        {
            return (0);
        }
        
        //ตรวจแนวตั้ง
        if (grid[i][col] == num)
        {
            return (0);
        }
        
        i++;
    }
    return (1);
}

int check_row_left(int grid[4][4], int row)
{
    int i;
    int max_height;
    int count;

    i = 0;
    max_height = 0;
    count = 0;
    while (i < 4)
    {
        if (grid[row][i] > max_height)
        {
            count++;
            max_height = grid[row][i];
        }
        i++;
    }
    return (count);
}

int check_row_right(int grid[4][4], int row)
{
    int i;
    int max_height;
    int count;

    i = 3;
    max_height = 0;
    count = 0;
    while (i >= 0)
    {
        if (grid[row][i] > max_height)
        {
            count++;
            max_height = grid[row][i];
        }
        i--;
    }
    return (count);
}

int check_col_top(int grid[4][4], int col)
{
    int i;
    int max_height;
    int count;

    i = 0;
    max_height = 0;
    count = 0;
    while (i < 4)
    {
        if (grid[i][col] > max_height)
        {
            count++;
            max_height = grid[i][col];
        }
        i++;
    }
    return (count);
}

int check_col_bottom(int grid[4][4], int col)
{
    int i;
    int max_height;
    int count;

    i = 3;
    max_height = 0;
    count = 0;
    while (i >= 0)
    {
        if (grid[i][col] > max_height)
        {
            count++;
            max_height = grid[i][col];
        }
        i--;
    }
    return (count);
}