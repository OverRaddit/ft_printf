
# ########## PFT ##########
echo -e '#########PFT##########' >> test_result.txt
git clone https://github.com/gavinfielder/pft.git pft
make re
cd pft
make re
./test
cat -e results.txt >> ../test_result.txt
cd ..

# ########## PFT_2019 ##########
echo -e '#########PFT_2019##########' >> test_result.txt
git clone https://github.com/gavinfielder/pft.git pft_2019
cd pft_2019
rm unit_tests.c
rm options-config.ini
git clone https://github.com/cclaude42/PFT_2019.git temp
cp temp/unit_tests.c .
cp temp/options-config.ini .
rm -rf temp
make re
./test
cat -e results.txt >> ../test_result.txt
cd ..
