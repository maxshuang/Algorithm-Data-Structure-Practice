/*
恰逢 H 国国庆，国王邀请 n 位大臣来玩一个有奖游戏。首先，他让每个大臣在左、右手上面分别写下一个整数，国王自己也在左、右手上各写一个整数。然后，让这 n 位大臣排成一排，国王站在队伍的最前面。排好队后，所有的大臣都会获得国王奖赏的若干金币，每位大臣获得的金币数分别是：排在该大臣前面的所有人的左手上的数的乘积除以他自己右手上的数，然后向下取整得到的结果。

国王不希望某一个大臣获得特别多的奖赏，所以他想请你帮他重新安排一下队伍的顺序，使得获得奖赏最多的大臣，所获奖赏尽可能的少。注意，国王的位置始终在队伍的最前面。

every person has <ai, bi>
objective: min(max())

This problem has an interesting best structure, 
for any two adjacent minister, max(bi1, ai*bi) <= max(bi, ai1*bi1) => max(ai*bi) <= max(ai1*bi1) 
this best structure must in the best solution 
*/

// n==2
int reward(int** numbers, int m, int n) {

}