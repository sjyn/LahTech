var app = angular.module("excel_app",[]);
app.controller('excel_controller', function($scope){
    $scope.sheet = [];
    init($scope);
});

function init($scope){
    $scope.sheet = [
        {
            b1: 0,
            b2: 0
        },
        {
            b1: 0,
            b2: 0
        },
        {
            b1: 0,
            b2: 0
        },
        {
            b1: 0,
            b2: 0
        }
    ];

    $scope.totals = [0,0,0,0,0];
    $scope.reorders = [false,false,false,false,false];

    $scope.reorderN1 = function (){
        $scope.countInd = 2;
        $scope.sheet.sort(function(obj1, obj2){
            var diff = obj1.b1 - obj2.b1;
            return diff;
            // var ud = $scope.reorders[0];
            // $scope.reorders[0] = !$scope.reorders[0];
            // if(ud){
            //     return diff;
            // } else {
            //     return (-1) * diff;
            // }
        });
    };
    $scope.reorderN2 = function(){
        $scope.countInd = 2;
        $scope.sheet.sort(function(o1,o2){
            return o1.b2 - o2.b2;
        });
    };
    $scope.reorderSum = function(){
        $scope.countInd = 2;
        $scope.sheet.sort(function(o1, o2){
            return (o1.b1 + o1.b2) - (o2.b1 + o2.b2);
        });
    };
    $scope.reorderProd = function(){
        $scope.countInd = 2;
        $scope.sheet.sort(function(o1, o2){
            return (o1.b1 * o1.b2) - (o2.b1 * o2.b2);
        })
    };
    $scope.reorderAvg = function(){
        $scope.countInd = 2;
        $scope.sheet.sort(function(o1, o2){
            return ((o1.b1 + o1.b2) / 2) - ((o2.b1 + o2.b2) / 2);
        })
    };

    $scope.addItem = function(){
        $scope.sheet.push({
            b1: 0,
            b2: 0
        });
        $scope.totals.push(0);
    };

    $scope.recalcTotals = function(){
        for(var i = 0; i < $scope.totals.length; i++){
            $scope.totals[i] = 0;
        }
        for(var i = 0; i < $scope.sheet.length; i++){
            var obj = $scope.sheet[i];
            $scope.totals[0] += obj.b1;
            $scope.totals[1] += obj.b2;
            $scope.totals[2] += obj.b1 + obj.b2;
            $scope.totals[3] += obj.b1 * obj.b2;
            $scope.totals[4] += (obj.b1 + obj.b2) / 2;
        }
    }
}
