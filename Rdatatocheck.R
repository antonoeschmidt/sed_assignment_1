setwd("~/Dropbox/Legatreise/RMIT/SoftwareEngine/assignment/sed_assignment_1")
library(e1071)
d <- read.table("data1.csv", header = TRUE, sep = ",")
getmode <- function(v) {
  uniqv <- unique(v)
  uniqv[which.max(tabulate(match(v, uniqv)))]
}
apply(d,2,mean)
apply(d,2,median)
apply(d,2,getmode)
apply(d,2,sd)
with(d, cov(x,y))
with(d, cor(x,y))
apply(d,2,skewness)
