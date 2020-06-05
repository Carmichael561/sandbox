#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

static int N, M;

bool find_house(int c, vector<vector<bool>>&graph, vector<bool>&seen, vector<int>&house_to_client)
{
    for (int h = 0; h < M; ++h)
    {
        if (graph[c][h] && !seen[h])
        {
            seen[h] = true;

            if (house_to_client[h]==-1 || find_house(house_to_client[h], graph, seen, house_to_client))
            {
                house_to_client[h] = c;
                return true;
            }
        }
    }
    return false;
}

int realEstateBroker(vector<vector<int>> clients, vector<vector<int>> houses) 
{
    N = clients.size();
    M = houses.size();
    vector<vector<bool>> graph(N, vector<bool>(M, false));

    for (int i = 0; i < N; ++i)
    {
        int mony = clients[i][1];
        int area = clients[i][0];
        for (int j = 0; j < M; ++j)
        {
            int price = houses[j][1];
            int sqware = houses[j][0];
            if (sqware > area && price <= mony)
            graph[i][j] = true;
        }
    }

    vector<int> house_to_client(M, -1);
    int ret = 0;

    for (int c = 0; c < N; ++c)
    {
        vector<bool> seen(M, false);
        bool find = find_house(c, graph, seen, house_to_client);
        if (find)
            ++ret;
    }

    return ret;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> clients(n);
    for (int clients_row_itr = 0; clients_row_itr < n; clients_row_itr++) {
        clients[clients_row_itr].resize(2);

        for (int clients_column_itr = 0; clients_column_itr < 2; clients_column_itr++) {
            cin >> clients[clients_row_itr][clients_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<vector<int>> houses(m);
    for (int houses_row_itr = 0; houses_row_itr < m; houses_row_itr++) {
        houses[houses_row_itr].resize(2);

        for (int houses_column_itr = 0; houses_column_itr < 2; houses_column_itr++) {
            cin >> houses[houses_row_itr][houses_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = realEstateBroker(clients, houses);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
