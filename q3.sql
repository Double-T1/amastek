SELECT p.product_name AS product, s.year, s.quantity * s.price AS total_amount
FROM SALES AS s
LEFT JOIN Product AS p
ON s.sales_id = p.product.id
ORDER BY s.year DESC