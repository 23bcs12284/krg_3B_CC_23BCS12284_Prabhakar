class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        
        vector<vector<int>> graph(n + 1);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        vector<vector<int>> dist(n + 1, vector<int>(2, INT_MAX));

        pq.push({0, 1});
        dist[1][0] = 0;

        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();

            int currtime = top.first;
            int node = top.second;

            for (int neigh : graph[node]) {
                int leavingtime;

                int temp=currtime / change;
                if ( temp% 2 == 0) {
                    
                    leavingtime = currtime + time;
                } else {
                
                    leavingtime = (temp + 1) * change + time;  

                }

                if (leavingtime < dist[neigh][0]) {
                    dist[neigh][1] = dist[neigh][0];
                    dist[neigh][0] = leavingtime;
                    pq.push({leavingtime, neigh});
                }
                else if (leavingtime > dist[neigh][0] && leavingtime < dist[neigh][1]) {
                    dist[neigh][1] = leavingtime;
                    pq.push({leavingtime, neigh});
                }
            }
        }

        return dist[n][1];
    }
};
