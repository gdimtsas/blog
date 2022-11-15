package com.example.inventory.domain;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;
import lombok.Data;

@Data
@Entity
@Table(name = "items")
public class Item {
    @Id
    private Integer id;
    private Integer quantity;
}
