$fileVersion = 1,11,3,0
$productVersion = 1,11,3,0

if ($Env:GITHUB_ACTIONS -eq "true") {
    $fileVersion[3] = [int]$Env:GITHUB_RUN_NUMBER
    $productVersion[3] = [int]$Env:GITHUB_RUN_NUMBER
}
