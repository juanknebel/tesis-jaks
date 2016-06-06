
RESTAURANT REVIEW COMPATIBILITY DATASET
=======================================

This dataset represents a graph, in which each node is a restaurant, and two nodes
are connected by a weighted edge. The weights in the edges indicate how similar
two restaurants are, based on the people who have written a review for both
restaurants.

FILES:

city_restaurant.txt (cityid, restaurantid)
	Mapping from cities to restaurants in that city.
restaurant_cost.txt (restaurantid, price)
	Mapping from restaurants to the average meal price in that restaurant.
restaurant_cuisine.txt (restaurantid, cuisineid)
	Mapping from restaurants to cuisine types served at that restaurant.
restaurant_compat_intersection.txt (restaurantid1, restaurantid2, inter)
	Restaurant compatibility: number of reviewers in common between the restaurants.	
restaurant_compat_jaccard.txt (restaurantid1, restaurantid2, jaccard)
	Restaurant compatibility: jaccard coefficient of reviewers of both restaurants.

--
Prepared by chato@yahoo-inc.com on Wed Jan 25 17:26:21 CET 2012
