// input�ɓ��̓f�[�^�S�̂�����
function Main(input) {
    var str = "CODEFESTIVAL2016"
	input = input.split("\n");
  	input = input[0].split("");
  	str = str.split("\n");
    str = str[0].split("");
    var index = 0;
    var sum=0;
    for(l of input){
      if(l != str[index]){
        sum++;
      }
      index++;
    }
	console.log(sum);
}
//*���̍s�ȍ~�͕ҏW���Ȃ��ł��������i�W�����o�͂����x�ɓǂݍ��݁AMain���Ăяo���܂��j
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
