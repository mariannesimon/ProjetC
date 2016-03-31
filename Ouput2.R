rm(list=ls())
library(ggplot2)

data = read.table("phasesuite.txt")
T = data$V1
A_init = data$V2
Ga = data$V3
Gb = data$V4
res = Ga

for (i in 1:length(res)){
  if (Gb[i]==0 && Ga[i]==0) res[i]=0 #Extinction
  else if (Gb[i]==0) res[i]=1 #Exclusion
  else res[i]=2 #Cohabitation
}
result = cbind(T,A_init,res)
etat <- factor(result[,3])
mescouleurs <- rainbow(n=9)
plot(result[,1], result[,2], pch = 20, 
     col = mescouleurs[etat],main="Diagramme de phase",
     xlab="T",ylab="Ainit")
legend("top", inset = 0.02, pch = 16, 
       legend = c("Extinction","Exclusion","Cohabitation"), 
       col = mescouleurs, cex=0.7)

p = ggplot(data=as.data.frame(result), 
           aes(x=T, y=A_init, colour=mescouleurs[etat]))
p <- p + geom_point(size=1)
p <- p + ggtitle("Diagramme de phase")
