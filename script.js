var ans=document.getElementById('answer');

function myFunction(value){
    ans.value+=value;
};

function myAns(){
    ans.value=eval(ans.value);
};


function clean(){
    ans.value='';
};

function backspace(){
    ans.value=ans.value.slice(0,-1);
}
