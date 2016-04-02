file = read.table("phase_d.txt")
T = file$V1
Ainit = file$V2
D = file$V3
Ga = file$V4
Gb = file$V5

res = Ga
for (i in 1:length(Ga)){
  if (Gb[i]==0 && Ga[i]==0) res[i]=0
  else if (Gb[i]==0) res[i] = 1
  else res[i] = 2
}
etat = factor(res)
mescouleurs <- rainbow(n=9)
df = data.frame(D,T,Ainit,Legende=mescouleurs[etat])
head(df)
p <- scatterplot3d(df,pch=20,main="Diagramme de phase")
p$points3d(df[,4])
