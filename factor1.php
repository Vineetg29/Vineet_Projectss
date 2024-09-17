#Code by Vineet_G
<?php
function findFactors($number) {
    $factors = array();
    for ($i = 1; $i <= $number; $i++) {
        if ($number % $i == 0) {
            $factors[] = $i;
        }
    }
	return $factors;
}
$number = 24;
$factors = findFactors($number);
echo "<br>Factors of $number are: ";
foreach ($factors as $factor) {
    echo "$factor ";
}
?>
