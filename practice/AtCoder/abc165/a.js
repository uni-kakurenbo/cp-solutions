// input�ɓ��̓f�[�^�S�̂�����
function Main(input) {
// 1�s�ڂ�input[0], 2�s�ڂ�input[1], �c�ɓ���
�@input = input.split("\n");
  k = ~~input[0]
�@a = ~~input[1].split(" ")[0];
  b = ~~input[1].split(" ")[1];
  let i=k;
  while (i <= b){
    if(i >= a && i <= b ){
      console.log("OK");
      return;
    }
    i += k;
  }
  console.log("NG")
  return;
}
//*���̍s�ȍ~�͕ҏW���Ȃ��ł��������i�W�����o�͂����x�ɓǂݍ��݁AMain���Ăяo���܂��j
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
