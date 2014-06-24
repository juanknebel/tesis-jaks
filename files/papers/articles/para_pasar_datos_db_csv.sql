#node_name.csv
SELECT b.item, a.title
FROM ARTICLES a, ARTICLE_ITEM b
WHERE a.ArticleId = b.ArticleId

#type_name.csv
SELECT a.VenueId, a.name
FROM VENUES a

#node_cover.csv
SELECT b.item, a.venue_VenueId
FROM ARTICLES a, ARTICLE_ITEM b
WHERE a.ArticleId = b.ArticleId

#node_cost.csv
SELECT a.Item, 1
FROM ARTICLE_ITEM a

#node_compatibility.csv
SELECT a.Item, a.Item2, a.Similarity
FROM SIMILARITY a