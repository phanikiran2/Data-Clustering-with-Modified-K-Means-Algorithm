# Data-Clustering-with-Modified-K-Means-Algorithm
### Overview <br/>

Cluster analysis is a descriptive task that seek to identify homogenous group of object and it is also one of the main analytical method in data mining. K-mean is the most popular partitional clustering method.But there are some short comings to these standard K-Means algorithm. Modified K-means implemented in this repository will overcome those short comings and improve speed and efficiency of the algorithm.</br>

### Short comings of K-Means <br/>
- Dead Unit Problem: As the initial centroid are selected randomly we might get a cluster where only a single or very few data points are assigned.
- Cluster formation depends on the Initial selection of clusters. 
### Improvement to K-Means <br/>
- In this modified K-Means algorithm instead of selecting  randomly the initial centroid, we segment the data set into K*K segments.
- We select centroid from high density or high frequency segment as there is high possibility that centroid is near to high density region or segment. 
- As initial centroids are selected from high density segments formation of a cluster with single or very few data points is void.
### Why Modified K-Means <br/>
- We use the modified k-mean algorithms because we want to  optimize the existing algorithm. Number of iterations will get reduced with this modified approach.
- To eliminate the dead Unit problem which arises beacuse of wrong selection of initial cluster centroid.
