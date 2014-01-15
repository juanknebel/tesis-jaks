#!/usr/bin/python
import MySQLdb

def generateArticlesOnly() :
  db = MySQLdb.connect(host="localhost", user="tesis", passwd="tesis", db="test")

  cur = db.cursor() 

  # Use all the SQL you like
  query = "select a.ArticleId as id, a.title as Title, b.name as Venue, a.year as Year,c.name as Author from ARTICLES a, VENUES b, AUTHORS c, Article_Author d where a.venue_VenueId=b.VenueId and a.ArticleId=d.ARTICLES_ArticleId and d.authors_AuthorId=c.AuthorId"
  cur.execute(query)

  # print all the first cell of all the rows
  articles = {}
  for row in cur.fetchall() :
    if(articles.has_key(row[0])) :
      articles[row[0]][2] = articles[row[0]][2] + ", " + row[4]
    else:
      articles[row[0]] = [row[1], row[3], row[4], row[2]]

  outputFile = open("ARTICLES.csv","w")
  outputFile.write("Paper\tYear\tAuthor\tVenue\n")

  for articleId in articles :
    for elem in articles[articleId] :
      outputFile.write(str(elem))
      outputFile.write("\t")
    outputFile.write("\n")

  outputFile.close()

def generateArticlesWithTopicProfile() :
  db = MySQLdb.connect(host="localhost", user="tesis", passwd="tesis", db="test")

  cur = db.cursor() 

  # Use all the SQL you like
  query = "select a.ArticleId as id,`a`.`title` AS `Title`,`a`.`year` AS `Year`,`b`.`name` AS `Venue`,`c`.`distribution` AS `Distribution`,`c`.`distribution_KEY` AS `Topic` from ((`ARTICLES` `a` join `VENUES` `b`) join `TopicProfile_distribution` `c`) where ((`a`.`venue_VenueId` = `b`.`VenueId`) and (`a`.`topicProfile_identifier` = `c`.`TopicProfile_identifier`)) order by `c`.`TopicProfile_identifier` desc"
  cur.execute(query)

  # print all the first cell of all the rows
  articles = {}
  for row in cur.fetchall() :
    if(articles.has_key(row[0])) :
      articles[row[0]][3] = articles[row[0]][3] + ", " + row[5] + " = " + str(row[4])
    else:
      articles[row[0]] = [row[1], row[2], row[3], row[5] + " = " + str(row[4])]

  outputFile = open("ARTICLES_PROFILES.csv","w")
  outputFile.write("Paper\tYear\tVenue\tTopicDistribution\n")

  for articleId in articles :
    for elem in articles[articleId] :
      outputFile.write(str(elem))
      outputFile.write("\t")
    outputFile.write("\n")

  outputFile.close()
  
if __name__ == '__main__':
  generateArticlesOnly()
  generateArticlesWithTopicProfile()