// input�ɓ��̓f�[�^�S�̂�����
function Main(input) {
	input = input.split("\n");
  �@input.shift();
    P = input
    var max = 0;
    var x;
    var sum = 0;
    for(i of P){
      if(max < i){
        x = Number(i) / 2
        max = Number(i);
      }
      sum += Number(i)
    }
    sum -= x   
    console.log(sum)
}
//*���̍s�ȍ~�͕ҏW���Ȃ��ł��������i�W�����o�͂����x�ɓǂݍ��݁AMain���Ăяo���܂��j
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
