#ifndef IDENTIFICATIONGENERETORARTICLE_H
#define IDENTIFICATIONGENERETORARTICLE_H

#include "identificationGeneretor.h"

class IdentificationGeneretorArticle : public IdentificationGeneretor {
public:
    IdentificationGeneretorArticle(Dao* dao) : IdentificationGeneretor(dao) {
        this->query = "SELECT \
                a.ArticleId as ArticleId \
                ,a.title as Title \
                ,b.name as VenueName \
                ,c.name as Author \
                FROM ARTICLES a, VENUES b, AUTHORS c, Article_Author d \
                WHERE a.venue_VenueId=b.VenueId and a.ArticleId=d.ARTICLES_ArticleId and \
                d.authors_AuthorId=c.AuthorId";
    }

    void fillTheMapping(MapStringString *node2name);

    ~IdentificationGeneretorArticle();
};

#endif // IDENTIFICATIONGENERETORARTICLE_H
