rm(list=ls())
library(ggplot2)

data = read.table("phase.txt")
T = data$V1
A_init = data$V2
Ga = data$V3
Gb = data$V4
res = Ga

for (i in 1:length(res)){
  if (Gb[i]==0 && Ga[i]==0) {
    res[i] = 0}
  else if (Gb[i]==0) {
    res[i]=1}
  else {
    if (Gb[i]/Ga[i] < 0.5) res[i] = 2
    else res[i] = 3}
}
df = data.frame(T,A_init,Etat=res)

p <- ggplot(data=df, 
            aes(x=T, y=A_init,colour=Etat))
# p <- p + scale_color_brewer(palette="Pastel1",labels=c("Extinction",
#                                                        "Exclusion","Cohabitation"))
# p + scale_color_manual(values=c("#2D2D2D",'#9DCD72',
#                                      '#56B4E9'),
#                        labels=c("Extinction",
#                                 "Exclusion","Cohabitation"))
p <- p + geom_point(size=1.5)
p <- p + ggtitle("Diagramme de phase sans mutation")
p
