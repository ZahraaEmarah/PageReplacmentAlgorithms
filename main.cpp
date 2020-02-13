#include <iostream>
#include <string.h>


int pos = 0;

int inQueue(int *arr, int number, int sizee)
{
    int i=0;
    for(i=0; i< sizee; i++)
    {
        if(arr[i] == number)
            return 0;
    }

    return 1;
}

int get_position(int *q, int element, int queue_n) /// gets position of an element in the queue
{
    int i;
    for(i=0; i< queue_n; i++)
    {
        if(q[i] == element)
        {
            return i;
        }
    }
}


int FIFO(int *arr, int queue_n, int arr_sizee)
{
    int queuee[queue_n-1];
    int index=0,j;
    int faults =0;
    int full =0;

    printf("Replacement Policy = FIFO\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    for(int i=0; i< arr_sizee; i++)
    {
        if(inQueue(queuee, arr[i], queue_n) == 0)
        {
            printf("%02d     ", arr[i]);
        }
        else
        {
            queuee[index%queue_n] = arr[i];
            index++;
            if(index > queue_n)
            {
                printf("%02d", arr[i]);
                printf(" F   ");
                faults++;
            }
            else
            {
                full++;
                printf("%02d     ", arr[i]);
            }
        }

        for(int i=0; i< full; i++)
        {
            printf("%02d ", queuee[i]);
        }
        printf("\n");
    }

    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", faults);

    return faults;
}

int LRU(int *arr, int queue_n, int arr_sizee)
{
    int queuee[queue_n-1];
    int index=0, MIN= 100,j;
    int faults =0;

    printf("Replacement Policy = LRU\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    for(int i=0; i< arr_sizee; i++)
    {
        MIN =100;
        if(inQueue(queuee, arr[i], queue_n) == 0)
        {
            printf("%02d     ", arr[i]);
        }
        else
        {
            int element;
            if(index >= queue_n)
            {
                printf("%02d", arr[i]);
                printf(" F   ");
                faults++;

                for(int k=0; k< queue_n; k++)
                {
                    for(j=i-1; j > 0; j--)
                    {
                        if(queuee[k] == arr[j])
                        {
                            if(j < MIN)
                            {
                               MIN = j;
                               element = arr[j];
                            }
                            break;
                        }
                    }
                }

                pos = get_position(queuee, element, queue_n);
                queuee[pos] = arr[i];
            }
            else
            {
                queuee[index%queue_n] = arr[i];
                index++;
                printf("%02d     ", arr[i]);
            }
        }

        for(int i=0; i< index; i++)
        {
            printf("%02d ", queuee[i]);
        }
        printf("\n");
    }

    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", faults);

    return faults;

}

int CLOCK(int *arr, int queue_n, int arr_sizee)
{
    int queuee[queue_n-1];
    int usebit[queue_n-1];
    int index=0,full=0;
    int faults =0;
    int pointer =0;

    printf("Replacement Policy = CLOCK\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    for(int i=0; i< arr_sizee; i++)
    {
        if(inQueue(queuee, arr[i], queue_n) == 0)
        {
            printf("%02d     ", arr[i]);
            pos = get_position(queuee, arr[i], queue_n);
            usebit[pos]=1;
        }
        else
        {
            if(index >= queue_n)
            {
                printf("%02d", arr[i]);
                printf(" F   ");
                faults++;

                while(usebit[pointer] != 0)
                {
                    usebit[pointer] = 0;
                    pointer++;
                    pointer = pointer % queue_n;
                }

                queuee[pointer] = arr[i];
                usebit[pointer] = 1;
                pointer++;
                pointer = pointer % queue_n;
            }
            else
            {
                queuee[index%queue_n] = arr[i];
                usebit[index%queue_n] = 1;
                index++;
                pointer = (index)%queue_n ;
                printf("%02d     ", arr[i]);
            }


        }

        for(int i=0; i< index; i++)
        {
            printf("%02d ", queuee[i]);
        }
        printf("\n");
    }

    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", faults);

    return faults;
}

int OPTIMAL(int *arr, int queue_n, int arr_sizee)
{
    int queuee[queue_n-1];
    int index=0,j;
    int faults =0;
    int MAX = -1;

    printf("Replacement Policy = OPTIMAL\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    for(int i=0; i< arr_sizee; i++)
    {
        MAX =0;
        if(inQueue(queuee, arr[i], queue_n) == 0)
        {
            printf("%02d     ", arr[i]);
        }
        else
        {
        int element;
            if(index >= queue_n)
            {
                printf("%02d", arr[i]);
                printf(" F   ");
                faults++;

                for(int k=0; k< queue_n; k++)
                {
                    int found =0;

                    for(int j=i; j< arr_sizee; j++)
                    {
                        if(queuee[k] == arr[j])
                        {
                            if(j > MAX)
                            {
                               MAX = j;
                               element = arr[j];
                            }
                            found = 1;
                        }
                    }

                    if(found == 0)
                    {
                        element = queuee[k];
                        break;
                    }
                }

                int pos = get_position(queuee, element, queue_n);
                queuee[pos] = arr[i];
            }
            else
            {
                queuee[index%queue_n] = arr[i];
                index++;
                printf("%02d     ", arr[i]);
            }
        }

        for(int i=0; i< index; i++)
        {
            printf("%02d ", queuee[i]);
        }
        printf("\n");
    }

    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", faults);

    return faults;

}

int main()
{
    char algo[10];

    int page;
    int pages[90];

    int i=0;
    int counter=0;
    int n;

    while(page != -1)
    {
        if(i == 1)
        {
            scanf("%s", algo);
        }
        else
        {
            scanf("%d", &page);
        }
        if(i == 0)
        {
            n = page;
        }
        if(page > -1 && i>1)
        {
            pages[counter] = page;
            counter++;
        }

        i++;
    }

    if(strcasecmp(algo,"fifo") == 0)
        FIFO(pages,n,counter);

    if(strcasecmp(algo,"lru") == 0)
        LRU(pages,n,counter);

    if(strcasecmp(algo,"optimal") == 0)
        OPTIMAL(pages,n,counter);

    if(strcasecmp(algo,"clock") == 0)
        CLOCK(pages,n,counter);

    return 0;
}
