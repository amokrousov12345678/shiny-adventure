//копипаста из старого референса, влом причесывать
ll g[105][105];

//поиск кратчайших рассто¤ний между каждой парой вершин за O(N^3)
for (int k=0;k<n;k++) {
       for (int i=0;i<n;i++) {
           for (int j=0;j<n;j++) {
               if (g[i][k]>=INF || g[k][j]>=INF) continue;
               g[i][j] = min(g[i][j], g[i][k]+g[k][j]);
               if (g[i][j]<-INF) g[i][j] = -INF;
           }
       }
   }

//проверка наличия отрицательного цикла: на главной диагонали появится отрицательное значение

   for (int i=0;i<n;i++) {
       if (g[i][i]<0) {
           cout << -1;
           return;
       }
   }