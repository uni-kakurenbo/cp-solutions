// input�ɓ��̓f�[�^�S�̂�����
function Main(input) {
// 1�s�ڂ�input[0], 2�s�ڂ�input[1], �c�ɓ���
  x = Number(input);
  m = 100;
  y = 0;
  while(m < x){
    m = Math.floor(m * 1.01);
    y++
  }
  console.log(y);
}
//*���̍s�ȍ~�͕ҏW���Ȃ��ł��������i�W�����o�͂����x�ɓǂݍ��݁AMain���Ăяo���܂��j
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
