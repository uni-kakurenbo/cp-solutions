// input�ɓ��̓f�[�^�S�̂�����
function Main(input) {
	input = input.split("\n");
  	input = input[0].split(" ");
    var A = Number(input[0])
    var B = Number(input[1])
    var T = Number(input[2])
    var time = 1;
    var sum = 0;
	for(var i=0; i<=(T+0.5); i++ ){
      if(i == time*A){
         sum += B;
         time++;
      }
    }
    console.log(sum)
}
//*���̍s�ȍ~�͕ҏW���Ȃ��ł��������i�W�����o�͂����x�ɓǂݍ��݁AMain���Ăяo���܂��j
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
