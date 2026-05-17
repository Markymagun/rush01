#include <unistd.h>

int check(char *str, int *arr)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (i % 2 == 0) //ตน.เลขคู่
		{
			if (str[i] >= '1' && str[i] <= '4')
			{
				arr[count] = str[i] - '0'; //แปลงเป็นตัวเลข เก็บลงarray
				count++;
			}
			else //เลขอื่นหรออักษรแปลกๆ
				return (0);
		}
		else ////ถ้าi(ตน.เลขคี่) เป็นเลข คี่ต้องมีช่องว่าง
		{
			if (str[i] != ' ')
				return (0);
		}
		i++;
	}
	if (count == 16 && i == 31) //เลข 16 ตัว + เว้นวรรค 15 ตัว = 31
		return (1);
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

int check_all(int grid[4][4], int *input)
{
    int i;

    i = 0;
    while(i < 4)
    {
        if (check_col_top(grid, i) != input[i])
            return (0);
        if (check_col_bottom(grid, i) != input[4 + i])
            return (0);
        if (check_row_left(grid, i) != input[8 + i])
            return (0);
        if (check_row_right(grid, i) != input[12 + i])
            return (0);
        i++;
    }
    return (1);
}

int solve(int grid[4][4], int *input, int pos)
{
	int row;
	int col;
	int num;

	if(pos == 16)
	{
		return (check_all(grid, input));
	}
	row = pos / 4;
	col = pos % 4;
	num = 1;
	while (num <= 4)
	{
		if (check_double(grid, row, col, num) == 1)
		{
			grid[row][col] = num;
			if (solve(grid, input, pos + 1) == 1)
			{
				return (1);
			}
			grid[row][col] = 0; //สมมติpos=5 แล้ววางเลข 4 ไปแล้วขยับไปpos=6 แล้วเติมเลขผิดไปต้อง reset(ใส่0)ที่pos=6 แล้วกลับมาpos=5
		}
		num++;
	}
	return (0);
}

void print_grid(int grid[4][4])
{
	int row;
	int col;
	char c;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			c = grid[row][col] + '0'; //เปลี่ยนint เป็น char เวลาrunจะเห็น
			write(1, &c, 1);
			if(col < 3)
			{
				write(1, " ", 1); //writeเว้นวรรคระหว่างตัวเลข
			}
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}

int main(int argc, char *argv[])
{
	int input[16];
	int grid[4][4];

	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	if (check(argv[1], input) == 0)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	init_grid(grid);
	if (solve(grid, input, 0) == 1)
	{
		print_grid(grid);
	}
	else
	{
		write(1, "Error\n", 6);
	}
	return (0);
}