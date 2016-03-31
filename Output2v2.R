rm(list=ls())
library(ggplot2)

data = read.table("phasesuite.txt")
T = data$V1
A_init = data$V2
Ga = data$V3
Gb = data$V4
res = Ga

for (i in 1:length(res)){
  if (Gb[i]==0 && Ga[i]==0) {
    res[i] = 'A'}
  else if (Gb[i]==0) {
    res[i]='B'}
  else {
    res[i] = 'C'}
}
etat <- factor(res)
mescouleurs <- rainbow(n=8)
df = data.frame(T,A_init,Legende=etat)

p <- ggplot(data=df, 
            aes(x=T, y=A_init,colour=Legende))
p <- p + scale_color_manual(values=c("#2D2D2D",'#D19030','#56B4E9'),
                            labels=c("Extinction","Exclusion","Cohabitation"))
p <- p + geom_point(size=1)
p <- p + ggtitle("Diagramme de phase")
p
