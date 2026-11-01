# Import necessary libraries
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler

# Step 1: Load the dataset
url = 'sales_data.csv'  # Update if stored locally
df = pd.read_csv(url)

# Step 2: Data Preprocessing
# Dropping unnecessary columns for clustering (ORDERNUMBER, ORDERDATE, etc.)
df = df[['QUANTITYORDERED', 'PRICEEACH', 'SALES', 'MONTH_ID', 'YEAR_ID']]

# Check for any null values
print("Null values:\n", df.isnull().sum())

# Scaling the data for K-means
scaler = StandardScaler()
scaled_data = scaler.fit_transform(df)

# Step 3: Determine the optimal number of clusters using the Elbow Method
inertia = []
K_range = range(1, 11)

for k in K_range:
    kmeans = KMeans(n_clusters=k, random_state=42)
    kmeans.fit(scaled_data)
    # inertia is the sum of squared distances of samples to their closest cluster center
    inertia.append(kmeans.inertia_)

# Plot the Elbow Graph
plt.figure(figsize=(8, 5))
plt.plot(K_range, inertia, marker='o')
plt.xlabel("Number of Clusters (k)")
plt.ylabel("Inertia")
plt.title("Elbow Method for Optimal k")
plt.show()

# Step 4: Apply K-Means with Optimal Number of Clusters (e.g., using k=4 after analyzing elbow plot)
optimal_k = 3  # Replace based on elbow plot observation
kmeans = KMeans(n_clusters=optimal_k, random_state=42)
df['Cluster'] = kmeans.fit_predict(scaled_data)


# Step 5: Visualize the Clusters
plt.scatter(df['QUANTITYORDERED'], df['SALES'], c=df['Cluster'])
plt.xlabel("Quantity Ordered")
plt.ylabel("Sales")
plt.title("K-Means Clustering")
plt.show()

print(df)
