data = read.table("phase.txt")
T = data$V1
A_init = data$V2
Ga = data$V3
Gb = data$V4
res = Ga
Legende = Ga

for (i in 1:length(res)){
  if (Gb[i]==0 && Ga[i]==0) {
    Legende[i]='Extincton'
    res[i] = 0}
  else if (Gb[i]==0) {
    res[i]=1
    Legende[i] = 'Exclusion'}
  else {
    Legende[i]='Cohabitation'
    res[i] = 2}
}
result = cbind(T,A_init,res)
etat <- factor(result[,3])
mescouleurs <- rainbow(n=10)

plot(result[,1], result[,2], 
     col = mescouleurs[etat],main="Diagramme de phase",
     xlab="T",ylab="Ainit")
legend("top", inset = 0.02, pch = 16, 
       legend = c("Extinction","Exclusion","Cohabitation"), 
       col = mescouleurs,  cex=0.6)

p = ggplot(data=as.data.frame(result), 
           aes(x=T, y=A_init,colours=mescouleurs[etat]))
p <- p + geom_point(size=1)
p <- p + scale_shape_discrete(labels=c("Extinction", "Exclusion", "Cohabitation"))
p <- p + ggtitle("Diagramme de phase")
p
Legende=mescouleurs[factor(Legende)]
fr = as.data.frame(result)
qplot(x=T,y=A_init,data=fr, col = mescouleursLegende)
