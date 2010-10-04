#ifndef DTW_H
#define DTW_H

#include <QList>
#include <QVector>

struct DTWResult
{
    float distance;
    QVector<QVector<int> > D;
};

class DTW
{
public:
    DTW();

    DTWResult classify(const QList<int> &templ, const QList<int> &observation);

    inline void init_int_array(int *a, int num_rows, int num_cols, int val)
    {
       int i;

       for( i = 0; i < num_rows * num_cols; i++)
          *(a + i) = val;
    }

};

#endif // DTW_H
