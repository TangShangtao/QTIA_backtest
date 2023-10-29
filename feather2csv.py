import pyarrow.feather as feather
import pandas as pd
baseDir = "/home/tangshangtao/test_data/20230102"
filename = "EXCHANGE_BINANCE.BTC-USDT.SECURITY_TYPE_PERP.CONTRACT_TYPE_LINEAR.USDT.UNSPECIFIED_bookSnapshot5_20230102.feather"
df : pd.DataFrame = feather.read_feather(baseDir + "/" + filename)
df.to_csv(baseDir + "/" + "BTCUSDT.csv")