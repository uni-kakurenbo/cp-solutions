// input�ɓ��̓f�[�^�S�̂�����
function Main(input) {
  �@input = Number(input)
    var num = 1000000007
    var P = 1;
    for(var i = 1; i <= input; i++){
      P *= Number(i)
      P %= num
    }
    console.log(P)
}
//*���̍s�ȍ~�͕ҏW���Ȃ��ł��������i�W�����o�͂����x�ɓǂݍ��݁AMain���Ăяo���܂��j
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
