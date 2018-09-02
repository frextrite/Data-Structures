#include <stdio.h>
#include <stdlib.h>

struct sparse;
void *add_element(struct sparse*, int, int, int);
struct sparse *get_sparse();
void print_sparse(struct sparse*);
void swap(int*, int*);
void transpose(struct sparse*);
int comparator(const void*, const void*);
void sort(struct sparse*);
int *create_row_start_index(struct sparse*);
int *create_row_end_index(struct sparse*);
struct sparse *multiply(struct sparse*, struct sparse*);
void print_matrix(struct sparse*);

struct sparse {
    int row, col, val;
};

void *add_element(struct sparse *matrix, int row, int col, int val) {
    matrix->row = row;
    matrix->col = col;
    matrix->val = val;
};

struct sparse *get_sparse() {
    int row, col, val;
    printf("Enter rows, column and number of non-zero elements in matrix: ");
    scanf("%d %d %d", &row, &col, &val);

    struct sparse *matrix = malloc((sizeof(struct sparse) * (val+1)));

    add_element(matrix, row, col, val);

    printf("Enter non-zero element row, column and value 1 by 1\n");
    for(int i = 1; i <= matrix->val; i++) {
        int r, c, v;
        scanf("%d %d %d", &r, &c, &v);
        add_element(matrix+i, r, c, v);
    }

    return matrix;
}

void print_sparse(struct sparse *matrix) {
    int non_zero_elements = matrix->val;

    for(int i = 0; i <= non_zero_elements; i++) {
        printf("%d %d %d\n", (matrix+i)->row, (matrix+i)->col, (matrix+i)->val);
    }
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void transpose(struct sparse *matrix) {
    int size = matrix->val;
    for(int i = 1; i <= size; i++) {
        swap(&(matrix+i)->row, &(matrix+i)->col);
    }
}

int comparator(const void *s1, const void *s2) {
    if(((struct sparse*)s1)->row == ((struct sparse*)s2)->row && ((struct sparse*)s1)->col > ((struct sparse*)s2)->col) {
        return 1;
    } else if(((struct sparse*)s1)->row > ((struct sparse*)s2)->row)  {
        return 1;
    } else {
        return -1;
    }

}

void sort(struct sparse *matrix) {
    qsort(matrix+1, matrix->val, sizeof(struct sparse), comparator);
}

int *create_row_start_index(struct sparse *matrix) {
    int *row_start = malloc(sizeof(int) * matrix->row);

    for(int i = 1; i <= matrix->val; i++) {
        if(*(row_start+((matrix+i)->row)) == 0) {
            *(row_start+((matrix+i)->row)) = i;
        }
    }

    return row_start;
}

int *create_row_end_index(struct sparse *matrix) {
    int *row_end = malloc(sizeof(int) * matrix->row);

    for(int i = 1; i < matrix->val; i++) {
        if((matrix+i)->row != (matrix+i+1)->row) {
            *(row_end+((matrix+i)->row)) = i;
        }
    }
    *(row_end+(matrix+matrix->val)->row) = matrix->val;

    return row_end;
}

struct sparse *multiply(struct sparse *m1, struct sparse *m2) {
    struct sparse *matrix = malloc(sizeof(struct sparse) * m1->row * m2->col);

    int r1, c1, v1;
    int r2, c2, v2;
    r1 = m1->row;
    c1 = m1->col;
    v1 = m1->val;
    r2 = m2->row;
    c2 = m2->col;
    v2 = m2->val;

    transpose(m2);
    sort(m2);

    int *row_start = create_row_start_index(m1);
    int *row_end = create_row_end_index(m1);

    int *col_start = create_row_start_index(m2);
    int *col_end = create_row_end_index(m2);


    struct sparse *start = matrix+1;
    int non_zero = 0;
    for(int i = 0; i < r1; i++) {
        for(int j = 0; j < c2; j++) {
            int r = *(row_start + i);
            int c = *(col_start + j);
            while(r <= *(row_end+i) && c <= *(col_end+j)) {
                if ((m1+r)->col == (m2+c)->col) {
                    int sum = start->val + (((m1+r)->val) * ((m2+c)->val));
                    add_element(start, (m1+r)->row, (m2+c)->row, sum);
                    r++;
                    c++;
                } else if((m1+r)->col > (m2+c)->col) {
                    c++;
                } else {
                    r++;
                }
            }

            if(start->val != 0) {
                start++;
                non_zero++;
            }

        }
    }

    add_element(matrix, r1, c2, non_zero);

    return matrix;
}

void print_matrix(struct sparse *matrix) {
    int k = 1;

    for(int i = 0; i < matrix->row; i++) {
        for(int j = 0; j < matrix->col; j++) {
            if( (matrix+k)->row == i && (matrix+k)->col == j ) {
                printf("%d", (matrix+k)->val);
                k++;
            } else {
                printf("0");
            }
            printf(" ");
        }
        printf("\n");
    }
}

int main() {
    struct sparse *m1;
    struct sparse *m2;

    m1 = get_sparse();
    m2 = get_sparse();

    printf("First matrix in normal form:\n");
    print_matrix(m1);

    printf("Second matrix in normal form:\n");
    print_matrix(m2);

    struct sparse *matrix = multiply(m1, m2);

    printf("Multiplication matrix in normal form:\n");
    print_matrix(matrix);

    return 0;
}