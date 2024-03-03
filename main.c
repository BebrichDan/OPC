#include <stdio.h>
#include "libs1/data_structures/matrix/matrix.h"
#include "libs1/algorithms/algorithm.h"
#include "libs1/data_structures/vector/vector.h"
#include "libs1/string/string_.h"
#include <math.h>

void swapRowsWithMaxMinElement(matrix *m)
{
    int iMaxRows = 0;
    int jMaxRows = getMaxIndex(m->values[iMaxRows], m->nCols);

    for (int i = 1; i < m->nRows; i++)
    {
        if (m->values[i][getMaxIndex(m->values[i], m->nCols)] > m->values[iMaxRows][jMaxRows])
        {
            jMaxRows = getMaxIndex(m->values[i], m->nCols);
            iMaxRows = i;
        }
    }

    int iMinRows = 0;
    int jMinRows = getMinIndex(m->values[iMinRows], m->nCols);

    for (int i = 1; i < m->nRows; i++)
    {
        if (m->values[i][getMinIndex(m->values[i], m->nCols)] < m->values[iMinRows][jMinRows])
        {
            jMinRows = getMinIndex(m->values[i], m->nCols);
            iMinRows = i;
        }
    }
    if (iMinRows != iMaxRows)
        swapRows(*m, iMinRows, iMaxRows);
}


int getMax(const int *a, int n)
{
    int maxElement = a[0];
    for (int i = 0; i < n; i++)
        if (a[i] > maxElement)
            maxElement = a[i];

    return maxElement;
}

void sortRowsByMinElement(matrix m)
{
    for (int i = m.nRows - 1; i >= 0; i--)
    {
        int iCurrentMax = i;
        int currentMax = getMax(m.values[i], m.nCols);
        for (int k = 0; k < i; k++)
            if (getMax(m.values[k], m.nCols) > currentMax)
            {
                currentMax = getMax(m.values[k], m.nCols);
                iCurrentMax = k;
            }
        if (iCurrentMax != i)
            swapRows(m, iCurrentMax, i);
    }
}


int getMin(const int *a, int n)
{
    int minElement = a[0];
    for (int i = 0; i < n; i++)
        if (a[i] < minElement)
            minElement = a[i];

    return minElement;
}

void sortColsByMinElement(matrix *m)
{
    *m = transposeMatrix(m);
    for (int k = 0; k < m->nRows; k++)
    {
        int iMin = k;
        int currentMin = getMin(m->values[iMin], m->nCols);
        for (int i = k + 1; i < m->nRows; i++)
        {
            if (getMin(m->values[i], m->nCols) < currentMin)
            {
                currentMin = getMin(m->values[i], m->nCols);
                iMin = i;
            }
        }
        if (iMin != k)
            swapRows(*m, iMin, k);
    }
    *m = transposeMatrix(m);
}


matrix productMatrices(matrix m1, matrix m2)
{
    int n = m1.nRows;
    matrix res = getMemMatrix(n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int sum = 0;
            for (int k = 0; k < n; k++)
            {
                sum += m1.values[i][k] * m2.values[k][j];
            }
            res.values[i][j] = sum;
            res.values[j][i] = sum;
        }
    }
    return res;
}

void getSquareOfMatrixIfSymmetric(matrix *m)
{
    if (isSymmetricMatrix(m))
    {
        matrix result = productMatrices(*m, *m);
        freeMemMatrix(m);
        *m = result;
    }
}


long long getSumLong(const int *a, int n)
{
    long long r = 0;
    for (int i = 0; i < n; i++)
        r += a[i];
    return r;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m)
{
    for (int i = 0; i < m.nRows; i++)
    {
        for (int j = i + 1; j < m.nRows; j++)
        {
            if (getSumLong(m.values[i], m.nCols) == getSumLong(m.values[j], m.nCols))
                return;
        }
    }
    m = transposeMatrix(&m);
}


bool isMutuallyInverseMatrices(matrix m1, matrix m2)
{
    matrix res1 = productMatrices(m1, m2);
    matrix res2 = productMatrices(m1, m2);
    if (isEMatrix(&res1) && isEMatrix(&res2))
    {
        freeMemMatrix(&res1);
        freeMemMatrix(&res2);
        return 1;
    }
    return 0;
}


matrix rotateRightMatrix(matrix *m)
{
    matrix resultMatrix = getMemMatrix(m->nCols, m->nRows);

    for (int i = 0; i < m->nRows; i++)
    {
        for (int j = 0; j < m->nCols; j++)
        {
            resultMatrix.values[m->nCols - 1 - j][i] = m->values[i][j];
        }
    }

    return resultMatrix;
}

int getMinInArea(matrix m)
{
    m = rotateRightMatrix(&m);
    position maxPos = getMaxValuePos(m);
    int minElement = m.values[maxPos.rowIndex][maxPos.colIndex];

    int lim = maxPos.rowIndex;
    int colLim = maxPos.colIndex;

    for (int i = lim - 1; i >= 1 & colLim > 0; i--)
    {
        if (getMin(m.values[i], colLim--) < minElement)
        {
            minElement = getMin(m.values[i], colLim + 1);
        }
    }

    int colLim2 = maxPos.colIndex + 1;
    for (int i = lim; i < m.nRows & colLim2 > 0; i++)
    {
        if (getMin(m.values[i], colLim2--) < minElement)
        {
            minElement = getMin(m.values[i], colLim2 + 1);
        }
    }

    return minElement;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m)
{
    m = rotateRightMatrix(&m);
    long long globalMax = 0;
    int currentMax = 0;
    for (int i = m.nRows - 1; i >= 0; i--)
    {
        if (i == 0)
            currentMax = m.values[0][0];
        else
        {
            for (int j = 0; j < m.nCols - 1 && i - j - 1 >= 0; j++)
            {
                currentMax = max(m.values[i - j][j], m.values[i - j - 1][j + 1]);
            }
        }
        globalMax += currentMax;
        printf("\n1 %d", currentMax);
    }

    for (int k = 1; k <= m.nCols - 1; k++)
    {
        if (k == m.nCols - 1)
        {
            currentMax = m.values[m.nRows - 1][k];
            printf("\n3 %d", currentMax);
        } else
        {
            for (int i = 1; i < m.nCols - k; i++)
            {
                currentMax = max(m.values[m.nRows - i][k], m.values[m.nRows - i - 1][k + 1]);
            }
            globalMax += currentMax;
            printf("\n2 %d", currentMax);
        }
    }
    return globalMax;
}

int countEqClassesByRowsSum(matrix m)
{
    if (m.nRows == 0)
        return 0;

    insertionSortRowsMatrixByRowCriteria(m, getSum);
    outputMatrix(m);

    int currentSumRow = getSum(m.values[0], m.nCols);
    int countEqClasses = 1;

    for (int i = 1; i < m.nRows; i++)
    {
        if (getSum(m.values[i], m.nCols) > currentSumRow)
            countEqClasses++;
        currentSumRow = getSum(m.values[i], m.nCols);
    }
    return countEqClasses;
}

int getNSpecialElement(matrix m)
{
    m = rotateRightMatrix(&m);
    int count = 0;
    for (int i = 0; i < m.nRows; i++)
    {
        for (int j = 0; j < m.nCols; j++)
        {
            if (m.values[i][j] > getSum(m.values[i], m.nCols) - m.values[i][j])
                count++;
        }
    }
    return count;
}

position getLeftMin(matrix m)
{
    return getMinValuePos(m);
}

void swapPenultimateRow(matrix m, int n)      // зачем это делать без изменения  матрицы
{
    position leftMin = getLeftMin(m);

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = m.values[leftMin.rowIndex++][leftMin.colIndex];
    }

    for (int i = n - 2, j = 0; j < n; j++)
    {
        m.values[i][j] = arr[j];
    }
    outputMatrix(m);
}

bool isNonDescendingSorted(int *a, int n)
{
    for (int i = 0; i < n - 1; i++)
        if (a[i] > a[i + 1])
            return false;
    return true;
}

bool hasAllNonDescendingRows(matrix m)
{
    for (int i = 0; i < m.nRows; i++)
    {
        if (!isNonDescendingSorted(m.values[i], m.nRows))
            return false;
    }
    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix)
{
    int countMatrices = 0;
    for (int i = 0; i < nMatrix; i++)
    {
        if (hasAllNonDescendingRows(ms[i]))
            countMatrices++;
    }
    return countMatrices;
}

bool isNullRow(const int *a, int n, int value)
{
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] == value)
            count++;
    }
    return count == n;
}

int countZeroRows(matrix m)
{
    int count = 0;
    for (int i = 0; i < m.nRows; i++)
    {
        if (isNullRow(m.values[i], m.nCols, 0))
            count++;
    }
    return count;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix)
{
    int largestNumberZeroRows = 2;                          //число заранее известное

    int count = 0;
    for (int i = 0; i < nMatrix; i++)
    {
        if (countZeroRows(ms[i]) == largestNumberZeroRows)
            count++;
    }
    printf("%d\n", count);
}

int abs(int a)
{
    return a > 0 ? a : -a;
}

int maxInArray(int *a, int n)
{
    int max = abs(a[0]);

    for (int i = 1; i < n; i++)
    {
        if (abs(a[i]) > max)
            max = abs(a[i]);
    }
    return max;
}

int maxAbsolutelyNorm(matrix m)
{
    int max = m.values[0][0];

    for (int i = 0; i < m.nRows; i++)
    {
        if (maxInArray(m.values[i], m.nCols) > max)
            max = maxInArray(m.values[i], m.nCols);
    }
    return max;
}

void printMinNorm(matrix *ms, int nMatrix)
{
    int minNorm = maxAbsolutelyNorm(ms[0]);

    for (int i = 1; i < nMatrix; i++)
    {
        if (maxAbsolutelyNorm(ms[i]) < minNorm)
            minNorm = maxAbsolutelyNorm(ms[i]);
    }

    for (int i = 0; i < nMatrix; i++)
    {
        if (maxAbsolutelyNorm(ms[i]) == minNorm)
            outputMatrix(ms[i]);
    }
}

int quantitySpecialElement(int *a, int n)                     //16
{
    int count = 0;
    for (int i = 1; i < n - 2; i++)
    {
        int left_max = a[0];
        int right_min = a[n - 1];
        for (int j = 1; j < i; j++)
        {
            if (a[j] > left_max)
                left_max = a[j];
        }
        for (int k = i + 1; k < n - 1; k++)
        {
            if (a[k] < right_min)
                right_min = a[k];
        }
        if (a[i] > left_max && a[i] < right_min)
            count++;
    }
    return count;
}

int getNSpecialElement2(matrix m)                               //16
{
    int count = 0;
    for (int i = 0; i < m.nRows; i++)
    {
        count += quantitySpecialElement(m.values[i], m.nCols);
    }
    return count;
}


double getScalarProduct(int *a, int *b, int n)
{
    double result = 0.0;
    for (int i = 0; i < n; i++)
    {
        result += a[i] * b[i];
    }
    return result;
}

double getVectorLength(int *a, int n)
{
    double result = 0.0;
    for (int i = 0; i < n; i++)
    {
        result += a[i] * a[i];
    }
    return sqrt(result);
}

double getCosine(int *a, int *b, int n)
{
    double scalarProduct = getScalarProduct(a, b, n);
    double lengthA = getVectorLength(a, n);
    double lengthB = getVectorLength(b, n);
    return scalarProduct / (lengthA * lengthB);
}

int getVectorIndexWithMaxAngle(matrix m, int *b)
{
    int maxIndex = -1;
    double maxCosine = -2.0;

    for (int i = 0; i < m.nRows; i++)
    {
        double cosine = getCosine(m.values[i], b, m.nCols);
        if (cosine > maxCosine)
        {
            maxCosine = cosine;
            maxIndex = i;
        }
    }

    return maxIndex;
}

long long getScalarProductRowAndCol(matrix m, int i, int j)
{
    long long res = 0;
    for (int k = 0; k < m.nRows; k++)
    {
        res += m.values[i][k] * m.values[k][j];
    }
    return res;
}

long long getSpecialScalarProduct(matrix m, int n)
{
    position max = getMaxValuePos(m);
    position min = getMinValuePos(m);
    return getScalarProductRowAndCol(m, max.rowIndex, min.colIndex);
}


int main()
{
    char s[] = {"e      \0"};
    printf("%s", findNonSpaceReverse(&s[7], s-1));

    return 0;
}

