// input�ɓ��̓f�[�^�S�̂�����
function Main(_inputStr) {
  const input = _inputStr
    .trim().split("\n")
    .map(_row => {
      return _row.trim().split(/\s+/)
        .map(_item => {const _num = Number(_item); return isNaN(_num) ? _item : _num})
    })
  //console.log(input)
  let [...S] = input;
  S = S.flat();
  //console.log(S)
  const C = ["ABC", "ARC", "AGC", "AHC"];
  console.log(C.find(_c => S.indexOf(_c) === -1));
}
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
