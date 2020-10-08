
#include <stdio.h>

#define MAX_USER 10000
#define MAX_QUESTION 5  

int N, K, M;
int top_cores[MAX_QUESTION];

typedef struct User {
  int user_id;
  int total_score;
  int scores[MAX_QUESTION];
}User;

User CreateUser(int user_id)
{
  int i;
  User U;
  U.user_id = user_id;
  U.total_score = 0;
  for(i = 0; i < K; i++) {
    U.scores[i] = -1;
  }
  return U;
}

int GetACNumber(User U)
{
  int i, ac_number = 0;
  for(i = 0; i < K; i++) {
    if(U.scores[i] == top_scores[i])
      ac_number++;
  }
  return ac_number;
}

int main()
{
  User users[MAX_USER];
  int table[MAX_USER];
  int i, j;
  int user_id, problem_id, score;
  scanf("%d %d %d", &N, &K, &M);
  for(i = 0; i < K; i++) {
    scanf("%d", &top_cores[i]);
  }
  for(i = 0; i < N; i++) {
    users[i] = CreateUser(i + 1);
    table[i] = i;
  }
  for(i = 0; i < M; i++) {
    scanf("%d %d %d", &user_id, &problem_id, &score);
    if(score < 0) {
      score = 0;
    }
    if(score > users[user_id - 1].scores[problem_id - 1]) {
      if(users[user_id - 1].scores[problem_id - 1] == -1) {
        users[user_id - 1].total_score += score;
      }else {
        users[user_id - 1].total_score += (score - users[user_id - 1].scores[problem_id - 1]);
      }
      users[user_id - 1].scores[problem_id - 1] = score;
    }
  }
  for(i = 1; i < N; i++) {
    int tmp = table[i];
    int tmp_score = users[i].total_score;
    if(tmp_score == 0) continue;
    for(j = i; j > 0; j--) {
      if(users[table[j - 1]].total_score < tmp_score) {
        table[j] = table[j - 1];
      }
      else if(users[table[j - 1]].total_score == tmp_score) {
        int ac_number = GetACNumber(users[i]);
        if(GetACNumber(users[table[j - 1]]) < ac_number) {
          table[j] = table[j - 1];
        }else {
          break;
        }
      }
      else {
        break;
      }
    } 
    table[j] = tmp;
  }
  int last_rank = 0;
  for(i = 0; i < N; i++) {
    User U = users[table[i]];
    if(i == 0 || U.total_score != users[table[i - 1]].total_score) {
      last_rank = i + 1;
    }
    if(U.total_score == 0) {
      if(i == 0) {
        printf("1 %d 0 - - - -", U.user_id);
      }
      break;
    } 
    printf("%d %.5d %d ", last_rank, U.user_id, U.total_score);
    for(j = 0; j < K; j++) {
      if(U.scores[j] == -1) {
        printf("-");
      }else {
        printf("%d", U.scores[j]);
      }
      if(j == K - 1) {
        printf("\n");
      }else {
        printf(" ");
      }
    }
  }
  return 0;
}