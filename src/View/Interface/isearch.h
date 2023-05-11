#ifndef ISEARCH_H
#define ISEARCH_H

#include <QString>

class ISearch
{
public:
    virtual void search(const QString& text) = 0;
};

#endif // ISEARCH_H
